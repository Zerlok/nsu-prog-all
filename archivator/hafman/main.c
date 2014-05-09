#include "haf.h"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("The encoded '%s' is '%s'\n", argv[1], encode(argv[1]));
	}
	else
	{
		printf("Simple example of haffma algorythm.\n");
		printf("The encode 'abracadabra' is '%s'\n", encode("abracadabra"));
	}
    return 0;
}
