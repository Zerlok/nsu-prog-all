#include "mod.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	char *chr=NULL;
	// char *chr;
	// arrayForSort = (int*)realloc( arrayForSort, sizeArrayForSort * sizeof(int) );
	int i = 0;
	int *lst = (int*) calloc(LEN, sizeof(int));

	if (lst == NULL) {
		printf("ERROR: Cannot create an array (Memory was not enough)!\n");
		return 0;
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-i")) {
				if ((i + 1) >= argc) {
					print_help();
					free(lst);
					return 0;
				} else {
					input = fopen(argv[i + 1], "r");

					if(input == NULL) {
						printf("ERROR: file '%s' does not exist!\n", argv[i + 1]);
						free(lst);
						return 0;
					} else {
						while (fscanf(input, '%s', chr) != EOF) {
							printf("'%s'\n", chr);
							// fgets(chr);
							i++;
						}
					}
					fclose(input);
				}
			}
		}
	} else {
		print_help();
	}
}


// int main_leha(int argc, char *argv[]) {
// 	FILE * inputFile = NULL;

// 	int i, j;
// 	int countElements = 0;
// 	int sizeArrayForSort = 10;
// 	int * arrayForSort = (int*)calloc( sizeArrayForSort, sizeof(int) );
	
// 	if( NULL == arrayForSort )
// 	{
// 		printf("> ERROR: memory was not allocate!\n");
// 		getch();
// 		return 0;
// 	}

// 	for(i = 1; i < argc; i++)
// 	{
// 		if( 0 == strcmp(argv[i], "-i") )
// 		{
// 			if( (i + 1) >= argc )
// 			{
// 				printf("ERROR: not ... arguments!\n");
// 				free(arrayForSort);
// 				getch();
// 				return 0;
// 			}

// 			inputFile = fopen(argv[i + 1], "r");

// 			if( NULL == inputFile )
// 			{
// 				printf("ERROR: file '%s' does not exist!\n", argv[i + 1]);
// 				free(arrayForSort);
// 				gethc();
// 				return 0;
// 			}

// 			i++;
// 		}
// 		else
// 		{
// 			if( NULL != inputFile )
// 			{
// 				printf("ERROR: too many arguments\n");
// 				free(arrayForSort);
// 				getch();
// 				return 0;
// 			}

// 			for(j = 0; j < strlen(argv[i]); j++)
// 				if(!isdigit(argv[i][j]))
// 				{
// 					printf("ERROR: incorrect input data was entered!\n");
// 					free(arrayForSort);
// 					getch();
// 					return 0;
// 				}

// 			arrayForSort[countElements] = atoi(argv[i]);
// 			countElements++;

// 			if(countElements == sizeArrayForSort)
// 			{
// 				sizeArrayForSort += 10;
// 				arrayForSort = (int*)realloc( arrayForSort, sizeArrayForSort * sizeof(int) );
// 				if( NULL == arrayForSort )
// 				{
// 					printf("> ERROR: memory was not allocate!\n");
// 					getch();
// 					return 0;
// 				}
// 			}
// 		}
// 	}


// 	getch();
// 	return 0;
// }