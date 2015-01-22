#ifndef __GRAPH_H__
#define __GRAPH_H__


// class Edge
// {
// 	public:
// 		Edge(std::auto_ptr<Edge> e);

// 		Edge(
// 				std::auto_ptr<Vertex> from,
// 				std::auto_ptr<Vertex> to,
// 				int weight = 0);
		
// 		~Edge();

// 		Vertex& get_begin();
// 		Vertex& get_end();
// 		int get_weight();

// 	private:
// 		int weight;
// 		Vertex& _begin;
// 		Vertex& _end;
// };


// class Vertex
// {
// 	public:
// 		Vertex(std::vector<Vertex>& nearest = {});
// 		~Vertex();

// 		Vertex(Vertex& v);

// 	private:
// 		std::vector< std::auto_ptr<Edge> > _edges;
// };


class AdjacencyMatrix
{
	public:
		AdjacencyMatrix(const int width);

		~AdjacencyMatrix();

		AdjacencyMatrix(const AdjacencyMatrix& m);

		const std::vector<int>& operator[](int v_index) const;

		bool is_linked(const int v1, const int v2) const;
		int count_edges(const int v_indx) const;
		const std::vector<int>& get_arounding_vertices(const int v_indx) const;

		void link(const int v1, const int v2);
		void link(const int v_indx, const std::vector<int>& vertices);

		void unlink(const int v1, const int v2);
		void unlink(const int v_indx, const std::vector<int>& vertices);

		void show() const;

	private:
		std::vector< std::vector<int> > _matrix;
};


class IncidenceMatrix
{
	public:
		IncidenceMatrix(const int v_num, const int e_num);
		~IncidenceMatrix();

		IncidenceMatrix(const IncidenceMatrix& g);

		const std::vector<int>& operator[](const int v_index) const;

		bool is_linked(const int v1, const int v2) const;
		int count_edges(const int v_indx) const;
		const std::vector<int>& get_arounding_vertices(const int v_indx) const;

		void link(const int v1, const int v2);
		void link(const int v_indx, const std::vector<int>& vertices);

		void unlink(const int v1, const int v2);
		void unlink(const int v_indx, const std::vector<int>& vertices);

		void show() const;

	private:
		std::vector< std::vector<int> > _matrix;
};


// __GRAPH_H__
#endif