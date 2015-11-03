#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "graph.h"


vector<Edge> get_all_adges(Graph &g)
{
	vector<Edge> edges;

	for (Vertex &v : g.get_vertices())
		for (Vertex &u : g.get_vertices())
		{
			Edge edge(&v, &u);

			if (edge.get_length() != Edge::zero_length)
				edges.push_back(edge);
		}

	return edges;
}


int main(int argc, char *argv[])
{
	// TODO: open file, read by lines (number, x, y)
//	Graph g({
//		Vertex(7, 5),
//		Vertex(-1, -8),
//		Vertex(2, -2),
//		Vertex(5, -8),
//		Vertex(14, -14),
//		Vertex(7, 10),
//		Vertex(3, 11),
//		Vertex(3, -11),
//		Vertex(1, 8),
//		Vertex(9, -15)
//	});
//	Graph g({
//		Vertex(0, 0),
//		Vertex(0, 1),
//		Vertex(0, 5),
//		Vertex(0, 10),
//		Vertex(0, 15),
//		Vertex(0, 18),
//		Vertex(0, 13),
//		Vertex(0, 21),
//		Vertex(0, 34),
//		Vertex(0, 55)
//	});
	Graph g({
		Vertex(7, 5),
		Vertex(3, -11),
		Vertex(2, -2),
		Vertex(-1, -8),
		Vertex(14, -14)
	});

	vector<Edge> edges = get_all_adges(g);
	sort(edges.begin(), edges.end());

	size_t vertices_num = g.get_vertices().size();
	for (Edge &edge : edges)
	{
		if (!g.is_linked(edge.get_begin(), edge.get_end()))
			g.add_edge(edge);

		if (g.get_edges().size() == vertices_num - 1)
			break;
	}

	// TODO: print the result tree (graph)
	g.print_edges_list(cout);
	cout << endl;
}

