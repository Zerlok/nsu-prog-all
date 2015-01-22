#include "main.h"

#include "graph.h"
#include "graphwalker.h"


int main(int argc, char **argv)
{
	AdjacencyMatrix graph(4);
	std::vector<int> vertices1 = {0, 2};
	std::vector<int> vertices2 = {1, 3};

	graph.show();

	graph.link(vertices1[0], vertices2);
	graph.link(vertices1[1], vertices2);

	graph.show();

	return 0;
}