#ifndef __TREEBUILDER_H__
#define __TREEBUILDER_H__


#include <algorithm>
using namespace std;

#include "graph.h"


bool equals_as_sets(const vector<Vertex::t_num_pair> &edges1, const vector<Vertex::t_num_pair> &edges2)
{
	if (edges1.size() != edges2.size())
		return false;

	size_t collisions_num = 0;

	for (const Vertex::t_num_pair &e1 : edges1)
		for (const Vertex::t_num_pair &e2 : edges2)
			if ((e1.first == e2.first)
					&& (e1.second == e2.second))
			{
				++collisions_num;
				break;
			}

	return (edges1.size() == collisions_num);
}


vector<Edge> get_all_adges(Graph &g)
{
	vector<Edge> edges;

	for (const Vertex &v : g.get_vertices())
		for (const Vertex &u : g.get_vertices())
		{
			Edge edge(&v, &u);

			if (edge.get_length() != Edge::zero_length)
				edges.push_back(edge);
		}

	return edges;
}


void build_tree(Graph &g)
{
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
}


// __TREEBUILDER_H__
#endif
