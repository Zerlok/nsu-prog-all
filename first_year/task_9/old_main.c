#include "head.h"

int main(int argc, char* argv[])
{
	NODE *head = NULL;
	int num;

	if (argc == 2)
	{
		if (strcmp(argv[1],"help") == 0)
		{
			printf("programma vsatvki chisla d yporyadochennai spisok");
			return 0;
		}
		if (freopen(argv[1], "r", stdin) == NULL) 
		{
			printf("Error with opennig file: %s\n",argv[1]);
			return 1;
		}
	}
	else if (argc > 2)
	{
		printf("Error, enter 1 argument\n");
		return 1;
	}
	/*
	перенаправление потока

	*/


	while (scanf("%d", &num) == 1)
	{
		if (insertNode(&head, num) == NULL)
		{
			printf("NOt enough Memory\n");

			return 1;
		}
	}
	/*
	счет чисел из потока, до первого не числа
	*/

	
	if(head)
	{
		printf("Sorted:\n");
		printnode(head);
	}
	/*
	вывод списка
	*/
}