#include <stdio.h>
#include <stdlib.h>

#include "longstring.h"
#include "recordarray.h"


void integer_printor(void *ptr)
{
	printf("%d, ", (
			(ptr != NULL) ? *((int*)ptr) : 0
	));
}


void recordarray_printor(void *ptr)
{
	ra_print((RecordArray*)ptr);
}


int run_subtask1()
{
	printf("Task 1: longstring. Type the text below.\n");

	t_longstring *text = get_longstring("Input text is:\n\0");
	t_longstring *double_paragraph = get_longstring("\n\n\0");

	while (!is_endswith_longstring(text, double_paragraph))
		append_longstring(text, getchar());
 
	print_longstring(text);

	destroy_longstring(text);
	destroy_longstring(double_paragraph);

	return 0;
}


int run_subtask2()
{
	printf("Task 2: recordarray. The tests are running...\n");

	RecordArray *arr1 = ra_create(10, sizeof(int));
	RecordArray *arr2 = ra_create(10, sizeof(int));
	
	int a[] = {33, 44, 55, 77, -1};
	ra_set(arr1, 0, (a + 3));
	ra_set(arr1, 1, (a + 2));
	ra_set(arr1, 2, (a + 1));
	ra_set(arr1, 3, a);

	arr1->f_element_printor = integer_printor;
	ra_print(arr1);

	ra_set(arr2, 0, (a));
	ra_set(arr2, 1, (a + 1));
	ra_set(arr2, 2, (a + 2));
	ra_set(arr2, 3, (a + 2));
	ra_set(arr2, 7, (a + 1));
	ra_set(arr2, 3, (a + 3));

	arr2->f_element_printor = integer_printor;
	ra_print(arr2);

	RecordArray *array = ra_create(2, sizeof(RecordArray));
	ra_set(array, 0, arr1);
	ra_set(array, 1, arr2);

	array->f_element_printor = recordarray_printor;
	ra_print(array);

	ra_delete(arr1);
	ra_delete(arr2);
	ra_delete(array);

	return 0;
}


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("One argument is required: the number of subtask.\n");
		return 1;
	}

	switch (argv[1][0])
	{
		case '1':
			return run_subtask1();

		case '2':
			return run_subtask2();

		default:
		{
			printf("Wrong number of subtask!\n");
			return 1;
		}
	}
}
