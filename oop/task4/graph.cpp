#include <vector>
using namespace std;

#include "graph.h"


const Vertex Graph::null_vertex = Vertex(0.0, 0.0, -1);
const double Graph::null_length = 0.0;


bool Graph::add_edge(const Vertex &v, const Vertex &u)
{
	if (has_edge(v, u))
		return false;

	_matrix[u.number][v.number] = _matrix[v.number][u.number] = v.count_distance_to(u);
	return true;
}


bool Graph::add_edge(const Edge &e)
{
	const Vertex &v = e.get_begin();
	const Vertex &u = e.get_end();

	if (has_edge(e))
		return false;

	_matrix[u.number][v.number] = _matrix[v.number][u.number] = e.get_length();
	return true;
}


const Vertex& Graph::operator[](int v) const
{
	return (has_vertex(v))
			? _vertices[v]
			: Graph::null_vertex;
}


bool Graph::is_isolated(const Vertex &v) const
{
	if (!has_vertex(v))
		return true;

	for (double len : _matrix[v.number])
		if (len > null_length)
			return false;

	return true;
}


bool Graph::has_edge(const Vertex &v, const Vertex &u) const
{
	return (has_vertex(v)
			&& has_vertex(u))
			? (_matrix[v.number][u.number] > null_length)
			: false;
}


bool Graph::has_edge(const Edge &e) const
{
	const Vertex &v = e.get_begin();
	const Vertex &u = e.get_end();

	return (has_edge(v, u)
			&& (e.get_length() == _matrix[v.number][u.number]));
}


bool Graph::is_linked(const Vertex &v, const Vertex &u) const
{
	return has_edge(v, u);
}


bool Graph::has_vertex(int v) const
{
	return ((v >= 0)
			&& (unsigned(v) < _vertices.size()));
}


bool Graph::has_vertex(const Vertex &v) const
{
	return (v != null_vertex)
			? has_vertex(v.number)
			: false;
}


void Graph::init_matrix()
{
	for (int i = 0; unsigned(i) < _vertices.size(); ++i)
		for (int j = 0; unsigned(j) < _vertices.size(); ++j)
			_matrix[i][j] = null_length;
}
