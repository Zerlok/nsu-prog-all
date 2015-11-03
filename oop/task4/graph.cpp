#include <vector>
using namespace std;

#include "graph.h"


const Vertex Vertex::none = Vertex(0.0, 0.0, -1, -1);
const double Edge::zero_length = 0.0;
Vertex none_vertex = Vertex(Vertex::none);


void Vertex::swap(Vertex &v)
{
	int tmp = v.number;
	v.number = number;
	number = tmp;

	tmp = v.color;
	v.color = color;
	color = tmp;
}


double distance(const Vertex &v, const Vertex &u)
{
	return sqrt(pow((v.x - u.x), 2)
				+ pow((v.y - u.y), 2));
}


ostream &operator<<(ostream &out, const Vertex &v)
{
	return out << "<Vertex id=" << v.number << " co=[" << v.x << " " << v.y << "] clr=" << v.color << ">";
}


ostream &operator<<(ostream &out, const Edge &e)
{
	return out << "<Edge len=" << e._length << " " << *(e._begin) << ", " << *(e._end) << ">";
}


Vertex& Graph::operator[](int v)
{
	return (has_vertex(v))
			? _vertices[v]
			: none_vertex;
}


const Vertex& Graph::operator[](int v) const
{
	return (has_vertex(v))
			? _vertices[v]
			: Vertex::none;
}


const Vertex &Graph::add_vertex(int x, int y)
{
	_vertices.push_back(Vertex(x, y, _vertices.size(), _vertices.size()));
	return _vertices.back();
}


Edge &Edge::operator=(const Edge &e)
{
	_begin = e._begin;
	_end = e._end;
	_length = e._length;

	return (*this);
}


bool Graph::connect(Vertex &v, Vertex &u)
{
	if (has_edge(v, u)
			|| (v == u))
		return false;

	if (v > u)
		v.swap(u);

	// Repaint linked vertices.
	if (v.color != u.color)
		repaint_linked_vertices(u, v.color);

	_edges.insert(make_pair(make_pair(v.number, u.number), Edge(&v, &u)));
	return true;
}


bool Graph::add_edge(Edge &e)
{
	Vertex &v = e.get_begin();
	Vertex &u = e.get_end();

	if (has_edge(e)
			|| (v == u)
			|| (e.get_length() <= Edge::zero_length))
		return false;

	if (v.color != u.color)
		repaint_linked_vertices(u, v.color);

	_edges.insert(make_pair(make_pair(v.number, u.number), e));
	return true;
}


bool Graph::has_edge(const Vertex &v, const Vertex &u) const
{
	if (!has_vertex(v)
			|| !has_vertex(u))
		return false;

	Vertex first(min<Vertex>(v, u));
	Vertex second(max<Vertex>(v, u));

	auto const it = _edges.find(make_pair(first.number, second.number));
	return (it != _edges.end())
			? (it->second.get_length() == distance(v, u))
			: false;
}


bool Graph::has_edge(const Edge &e) const
{
	if (!has_vertex(e.get_begin())
			|| !has_vertex(e.get_end()))
		return false;

	auto const it = _edges.find(make_pair(e.get_begin().number, e.get_end().number));
	return (it != _edges.end())
			? (it->second == e)
			: false;
}


bool Graph::is_linked(const Vertex &v, const Vertex &u) const
{
	return (has_vertex(v)
			&& has_vertex(u))
			? (v.color == u.color)
			: false;
}


bool Graph::is_isolated(const Vertex &v) const
{
	if (!has_vertex(v))
		return true;

	for (const Vertex &u : _vertices)
		if (has_edge(v, u))
			return false;

	return true;
}


bool Graph::has_vertex(int v) const
{
	return ((v >= 0)
			&& (unsigned(v) < _vertices.size()));
}


bool Graph::has_vertex(const Vertex &v) const
{
	return (v != Vertex::none)
			? has_vertex(v.number)
			: false;
}


Graph::Graph(const vector<Vertex> &vertices)
	: _vertices(vertices),
	  _edges()
{
	// Recalculate number of each vertex and make it isolated (set color to vertex num).
	for (int i = 0; unsigned(i) < _vertices.size(); ++i)
		_vertices[i].number = _vertices[i].color = i;
}


void Graph::repaint_linked_vertices(Vertex &v, int color)
{
	for (Vertex &u : _vertices)
		if ((u.color == v.color)
				&& (u != v))
			u.color = color;

	v.color = color;
}


ostream &operator<<(ostream &out, const Graph &g)
{
	return g.print_xml(out);
}


ostream &Graph::print_edges_list(ostream &out) const
{
	for (auto const it : _edges)
		out << it.first.first << " - " << it.first.second<< endl;

	return out;
}


ostream &Graph::print_xml(ostream &out) const
{
	out << "<Graph>" << endl;
	out << "\t<Vertices>" << endl;

	for (const Vertex &v : _vertices)
		out << "\t\t" << v << endl;

	out << "\t</Vertices>" << endl;
	out << "\t<Edges>" << endl;

	for (auto const it : _edges)
		out << "\t\t" << it.second << endl;

	out << "\t</Edges>" << endl;
	out << "</Graph>";

	return out;
}
