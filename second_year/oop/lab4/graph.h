#ifndef __GRAPH_H__
#define __GRAPH_H__


class Edge
{
	public:
		Edge(std::auto_ptr<Edge> e);

		Edge(
				std::auto_ptr<Vertex> from,
				std::auto_ptr<Vertex> to,
				int weight = 0);
		
		~Edge();

		Vertex& get_begin();
		Vertex& get_end();
		int get_weight();

	private:
		int weight;
		Vertex& _begin;
		Vertex& _end;
};


class Vertex
{
	public:
		Vertex(std::vector<Vertex>& nearest = {});
		~Vertex();

		Vertex(Vertex& v);

	private:
		std::vector< std::auto_ptr<Edge> > _edges;
};


class Graph
{
	Graph();
	~Graph();

	Graph(Graph& g);

	Vertex& operator[](const int index);

	const std::vector< std::auto_ptr<Vertex> >& get_vertices() const;
	const std::vector< std::auto_ptr<Edge> >& get_edges() const;
};


// __GRAPH_H__
#endif