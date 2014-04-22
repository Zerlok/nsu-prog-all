#include "haf.h"


int main(int argc, char **argv)
{
	char string[] = "abracadabra";

	if (argc == 2)
	{
		strcpy(string, argv[1]);
	}
	else
	{
		printf("Write a sequence of symbols to test hafman.\n");
		printf("For example 'abracadabra' will be:\n");
	}
	printf("string is: %s\n", string);
	printf("%s\n", encode(string));
	return 0;
}