#include <iostream>
using namespace std;

#include "graph.h"
#include "treebuilder.h"


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "One argument required - name of file with vertices coordinates." << endl;
		return 1;
	}

	Graph g(read_vertices(argv[1]));
	build_tree(g);
	g.print_edges_list(cout);

	return 0;
}
