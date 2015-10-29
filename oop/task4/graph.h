#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <math.h>
using namespace std;


// --------------------- VERTEX --------------------- //
class Vertex
{
	public:
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


// --------------------- EDGE --------------------- //
class Edge
{
	public:
		// Static.
		static const double zero_length;

		// Constructors / Destructor.
		Edge(Vertex *v, Vertex *u);
		Edge(const Vertex *v, const Vertex *u);
		Edge(const Edge &edge)
			: _begin(edge._begin),
			  _end(edge._end),
			  _length(edge._length) {}
		~Edge() {}

		// Operators.
		bool operator==(const Edge &e) const { return ((_begin == e._begin)
													   && (_end == e._end)
													   && (_length == e._length)); }

		// Friends.
		friend ostream &operator<<(ostream &out, const Edge &e);

		// Fields.
		const Vertex &get_begin() const { return (*_begin); }
		const Vertex &get_end() const { return (*_end); }
		double get_length() const { return _length; }

	private:
		Vertex *_begin;
		Vertex *_end;
		const double _length;
};


// --------------------- GRAPH --------------------- //

// For edge hash-table (key is a pair <int, int>).
typedef pair<int, int> t_vpair;
namespace std
{
	template<>
	class hash<t_vpair>
	{
		public:
			size_t operator()(const t_vpair& key) const
			{
				return (((hash<int>()(key.first)) << key.second)
						^ ((hash<int>()(key.second)) << key.first));
			}
	};
}

ostream &operator<<(ostream &out, const Edge &e);


class Graph
{
	public:
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
		const Vertex& operator[](int v) const;

		// Methods.
		const Vertex &add_vertex(int x, int y);
		bool connect(const Vertex &v, const Vertex &u);
		bool add_edge(const Edge &e);

		bool has_vertex(int v) const;
		bool has_vertex(const Vertex &v) const;

		bool has_edge(const Vertex &v, const Vertex &u) const;
		bool has_edge(const Edge &e) const;

		bool is_isolated(const Vertex &v) const;
		bool is_linked(const Vertex &v, const Vertex &u) const;

		set<Vertex> get_friends(const Vertex &v) const;

		// Friends.
		friend ostream &operator<<(ostream &out, const Graph &g);

	private:
		// Fields.
		vector<Vertex> _vertices;
		unordered_map<t_vpair, Edge> _edges;

		void repaint_linked_vertices(Vertex &v, int color);
};

ostream &operator<<(ostream &out, const Graph &g);


// __GRAPH_H__
#endif
