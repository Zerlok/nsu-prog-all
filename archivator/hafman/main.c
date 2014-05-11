#include "haf.h"

int main(int argc, char *argv[])
{
	// printf("Start '%s'\n", argv[1]);
	if (argc == 2)
	{
		printf("The encoded '%s' is '%s'\n", argv[1], encode(argv[1]));
	}
	else
	{
		printf("Simple example of haffman algorythm.\n");
		printf("The encoded 'abracadabra' is '%s'\n", encode("abracadabra"));
	}
    return 0;
}
