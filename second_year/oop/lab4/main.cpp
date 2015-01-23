#include "main.h"

#include "graph.h"
#include "graphwalker.h"


int main(int argc, char **argv)
{
	AdjacencyMatrix graph(6);
	std::vector<int> order;
	// std::vector<int> vertices = {1, 3};
	// IncidenceMatrix graph(6);

	graph.show();

	graph.link(0, 1);
	graph.link(0, 4);
	graph.link(1, 4);
	graph.link(1, 2);
	graph.link(2, 3);
	graph.link(3, 4);
	graph.link(3, 5);
	
	graph.show();

	walk_dfs<AdjacencyMatrix, int, std::vector<int> >(graph, 0, order);

	return 0;
}