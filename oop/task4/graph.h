#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <iostream>
#include <vector>
#include <unordered_map>
#include <math.h>
using namespace std;


// --------------------- VERTEX --------------------- //
class Vertex
{
	public:
		// Types.
		typedef pair<int, int> t_num_pair;

		// Static.
		static const Vertex none;

		// Constructors / Destructor.
		Vertex()
			: x(0),
			  y(0),
			  number(0),
			  color(none.color) {}
		Vertex(const Vertex &v)
			: x(v.x),
			  y(v.y),
			  number(v.number),
			  color(v.color) {}
		Vertex(int x, int y, int number=none.number+1, int color=none.color+1)
			: x(x),
			  y(y),
			  number(number),
			  color(color) {}
		~Vertex() {}

		// Operators.
		bool operator==(const Vertex &v) const { return (number == v.number); }
		bool operator!=(const Vertex &v) const { return (number != v.number); }
		bool operator<(const Vertex &v) const { return (number < v.number); }
		bool operator>(const Vertex &v) const { return (number > v.number); }

		// Methods.
		void swap(Vertex &v);

		// Friends.
		friend double distance(const Vertex &v, const Vertex &u);
		friend ostream &operator<<(ostream &out, const Vertex &v);

		// Fields.
		const int x;
		const int y;
		int number;
		int color;
};

double distance(const Vertex &v, const Vertex &u);
ostream &operator<<(ostream &out, const Vertex &v);
template<typename T> T* ptr_to_min(T *a, T *b)
{
	return (*a < *b)
			? a
			: b;
}
template<typename T> T* ptr_to_max(T *a, T *b)
{
	return (*a < *b)
			? b
			: a;
}


// --------------------- EDGE --------------------- //
class Edge
{
	public:
		// Static.
		static const double zero_length;

		// Constructors / Destructor.
		Edge(Vertex *v, Vertex *u)
			: _begin(ptr_to_min<Vertex>(v, u)),
			  _end(ptr_to_max<Vertex>(v, u)),
			  _length(distance(*_begin, *_end)) {}
		Edge(const Edge &edge)
			: _begin(edge._begin),
			  _end(edge._end),
			  _length(edge._length) {}
		~Edge() {}

		// Getters.
		Vertex &get_begin() { return (*_begin); }
		Vertex &get_end() { return (*_end); }
		Vertex *get_begin_ptr() { return _begin; }
		Vertex *get_end_ptr() { return _end; }
		const Vertex &get_begin() const { return (*_begin); }
		const Vertex &get_end() const { return (*_end); }
		const Vertex *get_begin_ptr() const { return _begin; }
		const Vertex *get_end_ptr() const { return _end; }
		double get_length() const { return _length; }

		// Operators.
		Edge &operator=(const Edge &e);
		bool operator<(const Edge &e) const { return (_length < e._length); }
		bool operator==(const Edge &e) const { return (_length == e._length); }

		// Friends.
		friend ostream &operator<<(ostream &out, const Edge &e);

	private:
		// Fields.
		Vertex *_begin;
		Vertex *_end;
		double _length;
};

ostream &operator<<(ostream &out, const Edge &e);


// --------------------- GRAPH --------------------- //

// For edge hash-table (key is a pair <int, int>).
namespace std
{
	template<>
	class hash<Vertex::t_num_pair>
	{
		public:
			size_t operator()(const Vertex::t_num_pair& key) const
			{
				return (((hash<int>()(key.first)) << key.second)
						^ ((hash<int>()(key.second)) << key.first));
			}
	};
}


class Graph
{
	public:
		// Types.
		typedef vector<Vertex> t_vertices;
		typedef unordered_map<Vertex::t_num_pair, Edge> t_edges;

		// Constructors / Destructor.
		Graph()
			: _vertices(),
			  _edges() {}
		Graph(const Graph &graph)
			: _vertices(graph._vertices),
			  _edges(graph._edges) {}
		Graph(const vector<Vertex> &vertices);
		~Graph() {}

		// Operators.
		Vertex& operator[](int v);
		const Vertex& operator[](int v) const;

		// Getters.
		t_vertices &get_vertices() { return _vertices; }
		t_edges &get_edges() { return _edges; }

		bool has_vertex(int v) const;
		bool has_vertex(const Vertex &v) const;

		bool has_edge(const Vertex &v, const Vertex &u) const;
		bool has_edge(const Edge &e) const;

		bool is_isolated(const Vertex &v) const;
		bool is_linked(const Vertex &v, const Vertex &u) const;

		// Methods.
		const Vertex &add_vertex(int x, int y);
		bool connect(Vertex &v, Vertex &u);
		bool add_edge(Edge &e);

		ostream &print_xml(ostream &out) const;
		ostream &print_edges_list(ostream &out) const;

		// Friends.
		friend ostream &operator<<(ostream &out, const Graph &g);

	private:
		// Fields.
		t_vertices _vertices;
		t_edges _edges;

		void repaint_linked_vertices(Vertex &v, int color);
};

ostream &operator<<(ostream &out, const Graph &g);


// __GRAPH_H__
#endif
