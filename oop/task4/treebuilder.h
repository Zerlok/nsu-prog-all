#ifndef __TREEBUILDER_H__
#define __TREEBUILDER_H__


#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;

#include "graph.h"


// ------------------------- ALGORYTHM ------------------------- //

vector<Edge> get_all_adges(Graph &g)
{
	vector<Edge> edges;

	for (size_t i = 0; i < g.get_size(); ++i)
	{
		for (size_t j = i + 1; j < g.get_size(); ++j)
		{
			Edge edge(&(g[i]), &(g[j]));

			if (edge.get_length() != Edge::zero_length)
				edges.push_back(edge);
		}
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


// ------------------------- EXTRA ------------------------- //

namespace std
{
	istream &operator>>(istream &in, Vertex::t_num_pair &pair)
	{
		int first;
		int second;
		in >> first >> second;

		pair.first = min<int>(first, second);
		pair.second = max<int>(first, second);

		return in;
	}

	ostream &operator<<(ostream &out, const Vertex::t_num_pair &pair)
	{
		out << "<Pair: " << pair.first << " - " << pair.second << ">";
		return out;
	}

	bool operator==(const vector<Vertex::t_num_pair> &edges1, const vector<Vertex::t_num_pair> &edges2)
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
};


const vector<Vertex::t_num_pair> read_pairs(const string &filename)
{
	ifstream input(filename);

	if (!input.is_open())
	{
		stringstream ss;
		ss << "Cannot read the file: " << filename;
		throw invalid_argument(ss.str());
	}

	vector<Vertex::t_num_pair> pairs;
	copy(istream_iterator<Vertex::t_num_pair>(input),
			  istream_iterator<Vertex::t_num_pair>(),
			  back_inserter(pairs));

	input.close();
	return pairs;
}


const vector<Vertex> read_vertices(const string &filename)
{
	ifstream input(filename);

	if (!input.is_open())
	{
		stringstream ss;
		ss << "Cannot read the file: " << filename;
		throw invalid_argument(ss.str());
	}

	vector<Vertex> vertices;
	copy(istream_iterator<Vertex>(input),
			  istream_iterator<Vertex>(),
			  back_inserter(vertices));

	input.close();
	return vertices;
}


// __TREEBUILDER_H__
#endif
