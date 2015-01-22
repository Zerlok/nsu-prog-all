#include "main.h"

#include "graph.h"
#include "graphwalker.h"


int main(int argc, char **argv)
{
	AdjacencyMatrix graph(4);
	std::vector<int> vertices = {1, 3};

	graph.show();

	graph.link(0, vertices);
	graph.link(2, vertices);

	graph.show();

	graph.unlink(0, 1);

	graph.show();
	return 0;
}