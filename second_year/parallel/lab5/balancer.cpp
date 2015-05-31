#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>


#define SIZE 10
#define EASY_TASK 1
#define HARD_TASK 5
#define EASY_RANK 0
#define MASTER 0


#define ASK 0
#define POSITIVE_ANSWER 1
#define NEGATIVE_ANSWER 2
#define STATUS_OK 3
static const int PROTOCOL[] = {
	ASK,
	POSITIVE_ANSWER,
	NEGATIVE_ANSWER,
	STATUS_OK
};


#define TAG_QUERRY 1230
#define TAG_ANSWER 1431
#define TAG_TASK 1124
#define TAG_FINISHED 1811
#define END 1662


typedef int Task;

int global_flag = 0;
int currentTask;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_f = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_finish = PTHREAD_MUTEX_INITIALIZER;

MPI_Status status;
int mpi_rank, mpi_size;
int readyTasks;
int finished_processes;
int *processes;
pthread_t thrs[2];


int askForTask(Task* pool);
void *taskHandler(void *pool);
void fillPool(Task pool[SIZE]);
void* balancer(void* pool);


int main(int argc, char** argv){
	Task pool[SIZE];
	int i;
	int k;
	int provided;
	double t1, t2;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
	
	if (provided != MPI_THREAD_MULTIPLE){
		perror("cant work");
		return -1;
	}

	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	processes = (int*)calloc(mpi_size, sizeof(int));

	pthread_attr_t attrs;
	fillPool(pool);

	if (0 != pthread_attr_init(&attrs))
	{
		perror("Cannot initialize attributes");
		return -1;
	};

	if (0 != pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE))
	{
		perror("Error in setting attributes");
		return -1;
	}
	if (0 != pthread_create(&thrs[0], &attrs, taskHandler, pool))
	{
		perror("Cannot create a thread");
		return -1;
	}
	if (0 != pthread_create(&thrs[1], &attrs, balancer, pool))
	{
		perror("Cannot create a thread");
		return -1;
	}

	if (mpi_rank == MASTER)
	{
		t1 = MPI_Wtime();
	}

	for (i = 0; i < 2; i++)
	{
		if (0 != pthread_join(thrs[i], NULL))
		{
			perror("Cannot join a thread");
			return -1;
		}
	}

	if (mpi_rank == MASTER)
	{
		t2 = MPI_Wtime();
		printf("SIZE:%d\tTIME:%lf\n", mpi_size, t2-t1);
	}

	pthread_mutex_destroy(&mutex);
	MPI_Finalize();
	pthread_attr_destroy(&attrs);

	return(0);
}


int askForTask(Task* pool)
{
	int i;
	int answer;
	pthread_mutex_lock(&mutex_f);
	for (i = 0; i < mpi_size; i++)
	{
		if (i == mpi_rank || processes[i] == END)
			continue;

		MPI_Ssend(&mpi_rank, 1, MPI_INT, i, TAG_QUERRY, MPI_COMM_WORLD);
		MPI_Recv(&answer, 1, MPI_INT, i, TAG_ANSWER, MPI_COMM_WORLD, &status);

		if (answer == POSITIVE_ANSWER)
		{
			--currentTask;
			MPI_Recv(&(pool[currentTask]), 1, MPI_INT, i, TAG_TASK, MPI_COMM_WORLD, &status);
			pthread_mutex_unlock(&mutex_f);
			return 0;
		}
	}

	pthread_mutex_unlock(&mutex_f);
	for (i = 0; i < mpi_size; i++)
	{
		if (i == mpi_rank)
			continue;
		
		int tmp = -mpi_rank - 1;
		MPI_Ssend(&tmp, 1, MPI_INT, i, TAG_QUERRY, MPI_COMM_WORLD);
	}

	i = 0;
	while (i < mpi_size - 1)
	{
		int answer;
		MPI_Recv(&answer, 1, MPI_INT, MPI_ANY_SOURCE, TAG_FINISHED, MPI_COMM_WORLD, &status);
		
		if (answer == STATUS_OK){
			i++;
		}
		else{
			perror("bad finish answers");
		}
	}
	
	pthread_mutex_lock(&mutex_finish);
	global_flag = 1;
	pthread_mutex_unlock(&mutex_finish);
	return 1;
}

void *taskHandler(void *pool)
{
	int time;
	pthread_mutex_lock(&mutex);
	currentTask = 0;
	pthread_mutex_unlock(&mutex);

	while (1)
	{
		pthread_mutex_lock(&mutex);
		
		if (currentTask == SIZE)
		{
			if (askForTask((Task*)pool))
			{
				pthread_mutex_unlock(&mutex);
				break;
			}
		}

		fprintf(stderr, "taskHandler %d: currentTask %d\n", mpi_rank, currentTask);
		time = ((Task*)pool)[currentTask];
		currentTask++;
		pthread_mutex_unlock(&mutex);
		
		fprintf(stderr, "taskHandler %d: sleep %d\n", mpi_rank, time);
		sleep(time);
		readyTasks++;
		
		fprintf(stderr, " ReadyTasks (mpi_rank %d) = %d\n", mpi_rank, readyTasks);
	}

	fprintf(stderr, "finish task handler %d\n", mpi_rank);
	return NULL;
}

void* balancer(void* pool)
{
	int answer;
	int finishedProcessRank;
	
	while (1)
	{
		pthread_mutex_lock(&mutex_finish);
		if (global_flag)
			break;
		
		pthread_mutex_unlock(&mutex_finish);

		MPI_Recv(&answer, 1, MPI_INT, MPI_ANY_SOURCE, TAG_QUERRY, MPI_COMM_WORLD, &status);

		if (answer < 0)
		{
			finishedProcessRank = -answer - 1;
			pthread_mutex_lock(&mutex_f);
			processes[finishedProcessRank] = END;
			pthread_mutex_unlock(&mutex_f);
			MPI_Ssend(&(PROTOCOL[STATUS_OK]), 1, MPI_INT, finishedProcessRank, TAG_FINISHED, MPI_COMM_WORLD);
			finished_processes++;
			
			if (finished_processes == mpi_size - 1)
				break;

			continue;
		}

		fprintf(stderr, "balancer %d: querry from %d\n", mpi_rank, answer);
		pthread_mutex_lock(&mutex);
		
		if (currentTask == SIZE)
		{
			MPI_Ssend(&(PROTOCOL[NEGATIVE_ANSWER]), 1, MPI_INT, answer, TAG_ANSWER, MPI_COMM_WORLD);
			fprintf(stderr, "balancer %d: negative answer\n", mpi_rank);
		}
		else
		{
			fprintf(stderr, "balancer %d: positive answer %d\n", mpi_rank, answer);
			MPI_Ssend(&(PROTOCOL[POSITIVE_ANSWER]), 1, MPI_INT, answer, TAG_ANSWER, MPI_COMM_WORLD);
			MPI_Ssend(&(((Task*)pool)[currentTask]), 1, MPI_INT, answer, TAG_TASK, MPI_COMM_WORLD);
			currentTask++;
		}
		
		pthread_mutex_unlock(&mutex);
	}

	pthread_mutex_unlock(&mutex_finish);
	fprintf(stderr, "finish balancer %d\n", mpi_rank);
	
	return NULL;
}

void fillPool(Task pool[SIZE])
{
	int k;

	for (k = 0; k < SIZE; k++)
	{
		if (mpi_rank == EASY_RANK){
			pool[k] = EASY_TASK;
		}
	
		else if(mpi_rank == 1){
			pool[k] = HARD_TASK;
		}
	
		else if (mpi_rank == 2){
			pool[k] = 1;
		}
	
		else
		{
			pool[k] = 1;
		}
	}
}