#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_WORK struct timespec start, end;
#define RUN_WORK clock_gettime(CLOCK_MONOTONIC_RAW, &start);
#define END_WORK clock_gettime(CLOCK_MONOTONIC_RAW, &end);
#define COUNT_WORK printf("Duration is %lf sec.\n", end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec));


void print_list(int *list, int len)
{
	int i;

	printf("Sorted: [");
	for (i = 0; i < len; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\b]\n");
}


int *get_int_list_from_argv(char **argv_list, int len)
{
	int i;
	int *num_list = (int*)malloc(len - 1);

	for (i = 0; i < len - 1; i++)
	{
		num_list[i] = atoi(argv_list[i + 1]);
	}

	return num_list;
}


int bubble_sort(int *list, int len)
{
	int i, j, chg;

	for (i = 0; i < len; i++)
	{
		for (j = i; j < len; j++)
		{
			if (list[j] < list[i])
			{
				chg = list[j];
				list[j] = list[i];
				list[i] = chg;
			}
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{
	int i, *list = NULL;
	INIT_WORK

	if (argc == 1)
	{
		printf("Write an array to sort.\n");
	}
	else
	{
		list = get_int_list_from_argv(argv, argc);

		RUN_WORK
		bubble_sort(list, argc-1);
		END_WORK

		print_list(list, argc-1);

		COUNT_WORK
	}
	return 0;
}