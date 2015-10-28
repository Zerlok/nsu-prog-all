#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <vector>
#include <list>
#include <set>
#include <math.h>
using namespace std;


class Vertex
{
	public:
		// Constructors / Destructor.
		Vertex()
			: x(0),
			  y(0),
			  number(0) {}
		Vertex(const Vertex &v)
			: x(v.x),
			  y(v.y),
			  number(v.number) {}
		Vertex(int x, int y, int number=0)
			: x(x),
			  y(y),
			  number(number) {}
		~Vertex() {}

		// Operators.
		bool operator==(const Vertex &v) const { return ((number == v.number)
														 && (x == v.x)
														 && (y == v.y)); }
		bool operator!=(const Vertex &v) const { return !(this->operator==(v)); }

		// Methods.
		double count_distance_to(const Vertex &v) const { return sqrt(pow((x - v.x), 2) + pow((y - v.y), 2)); }

		// Fields.
		const int x;
		const int y;
		const int number;
};


class Edge
{
	public:
		// Constructors / Destructor.
		Edge(const Edge &edge)
			: _begin(edge._begin),
			  _end(edge._end),
			  _length(edge._length) {}
		Edge(const Vertex &v1, const Vertex &v2)
			: _begin(v1),
			  _end(v2),
			  _length(_begin.count_distance_to(_end)) {}
		~Edge();

		// Getters.
		const Vertex &get_begin() const { return _begin; }
		const Vertex &get_end() const { return _end; }
		double get_length() const { return _length; }

	private:
		// Fields.
		const Vertex _begin;
		const Vertex _end;
		const double _length;
};


class Graph
{
	public:
		// Static.
		static const Vertex null_vertex;
		static const double null_length;

		// Constructors / Destructor.
		Graph()
			: _vertices(),
			  _matrix() { init_matrix(); }
		Graph(const Graph &graph)
			: _vertices(graph._vertices),
			  _matrix(graph._matrix) { init_matrix(); }
		Graph(const vector<Vertex> &vertices)
			: _vertices(vertices),
			  _matrix() { init_matrix(); }
		~Graph() {}

		// Getters.
		int get_vertices() const;
		int get_edges() const;
		const Vertex& operator[](int v) const;

		// Methods.
		bool add_edge(const Vertex &v, const Vertex &u);
		bool add_edge(const Edge &e);
		bool has_vertex(int v) const;
		bool has_vertex(const Vertex &v) const;
		bool has_edge(const Vertex &v, const Vertex &u) const;
		bool has_edge(const Edge &e) const;
		bool is_isolated(const Vertex &v) const;
		bool is_linked(const Vertex &v, const Vertex &u) const;
		set<Vertex> get_friends(int v) const;

		// Iterators.
		class VertexIterator
		{
			public:
				VertexIterator(int v);
				VertexIterator(const VertexIterator &vit);

			private:
				set<Vertex> _visited;
		};

		class EdgeIterator;

	private:
		// Fields.
		vector<Vertex> _vertices;
		vector<vector<double>> _matrix;

		// Methods.
		void init_matrix();
};


// __GRAPH_H__
#endif
