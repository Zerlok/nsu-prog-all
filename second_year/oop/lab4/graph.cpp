#include "main.h"

#include "graph.h"


Edge::Edge(
		std::auto_ptr<Edge> e)
	: _begin(e->_begin),_end(e->_end), _weight(e->_weight) {}

Edge::Edge(
		std::auto_ptr<Vertex> from,
		std::auto_ptr<Vertex> to,
		int weight = 0)
	: _begin(from), end(to), _weight(weight) {}


Vertex& Edge::get_begin()
{
	return *_begin;
}


Vertex& Edge::get_end()
{
	return *_end;
}


int get_weight()
{
	return _weight;
}


Vertex::Vertex(std::vector<Vertex>& nearest)
{
	for (auto v = nearest.begin();
		v != nearest.end();
		v++)
		_edges.push_back(new Edge(this, (*v)));
}


Vertex::~Vertex()
{

}


Vertex::Vertex(Vertex& v)
{

}
