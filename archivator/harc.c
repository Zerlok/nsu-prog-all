#include "mod.h"


int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		read_tags(argc, argv);
	}
	else
	{
		print_doc();
	}
	return 0;
}