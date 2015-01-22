#include "main.h"

#include "graph.h"
#include "graphwalker.h"


int main(int argc, char **argv)
{
	Graph G(1, {});

	walk_dfw(G);

	return 0;
}