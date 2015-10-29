#include <iostream>
using namespace std;

#include "graph.h"


int main(int argc, char *argv[])
{
	// TODO: open file, read by lines (number, x, y)
	// TODO: count smallest edges
	// TODO: add edge to tree (graph), if not a cycle, repeat unitl |E| - 1 < |V|
	// TODO: print the result tree (graph)

	Graph g({
			Vertex(0, 1),
			Vertex(1, 1),
			Vertex(10, 1),
			Vertex(-5, 3),
			Vertex(17, 7),
			Vertex(13, -13)
	});
	g.connect(g[0], g[1]);
	g.connect(g[3], g[4]);
	g.connect(g[2], g[1]);
	g.connect(g[2], g[3]);

	cout << g << endl;
}

