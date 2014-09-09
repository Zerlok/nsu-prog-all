#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_WORK struct timespec start, end;
#define RUN_WORK clock_gettime(CLOCK_MONOTONIC_RAW, &start);
#define END_WORK clock_gettime(CLOCK_MONOTONIC_RAW, &end);
#define COUNT_WORK printf("Duration is %lf sec.\n", end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec));


void print_list(long long int *list, long long int len)
{
	long long int i;

	printf("Sorted: [");
	for (i = 1; i <= len; i++)
	{
		printf("%lld ", list[i]);
	}
	printf("\b]\n");
}


int bubble_sort(long long int *list, long long int len)
{
	long long int i, j, chg;

	for (i = 1; i <= len; i++)
	{
		for (j = i; j <= len; j++)
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


long long int *get_unsorted_int_list(long long int len)
{
	long long int i;
	long long int *num_list = (long long int*)malloc(sizeof(long long int) * len);

	for (i = len; i >= 0; i--)
	{
		num_list[len - i + 1] = i;
	}

	return num_list;
}


int main(int argc, char *argv[])
{
	long long int *list = NULL;
	INIT_WORK

	if (argc == 1)
	{
		printf("Write the length of array to sort it.\n");
	}
	else
	{
		long long int len = atoi(argv[1]);
		list = get_unsorted_int_list(len);

		RUN_WORK
		bubble_sort(list, len);
		END_WORK

		print_list(list, len);

		COUNT_WORK
	}
	return 0;
}
