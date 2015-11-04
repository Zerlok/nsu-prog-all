#include <iostream>
#include <vector>
using namespace std;

#include "graph.h"
#include "treebuilder.h"


int main(int argc, char *argv[])
{
//	// TODO: open file, read by lines (number, x, y)
//	Graph g({
//			Vertex(0, 0),
//			Vertex(0, 2),
//			Vertex(2, 0),
//			Vertex(2, 2),
//			Vertex(1, 1)
//	});

////	build_tree(g);
//	cout << g.connect(g[0], g[1]) << endl;
//	cout << g.connect(g[0], g[1]) << endl;

//	// TODO: print the result tree (graph)
//	g.print_edges_list(cout);
//	cout << endl;

	Graph g({
		Vertex(7, 5),
		Vertex(3, -11),
		Vertex(2, -2),
		Vertex(-1, -8),
		Vertex(14, -14)
	});

	build_tree(g);
	vector<Vertex::t_num_pair> connections = g.get_connections();

	cout << connections.size() << endl;
	for (const Vertex::t_num_pair &p : connections)
		cout << p.first << " - " << p.second << endl;
}

