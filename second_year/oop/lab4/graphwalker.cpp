#include "main.h"

#include "graphwalker.h"


// template <class VertexType = int>
// void show_vertex(VertexType& v)
// {
// 	std::cout << v << std::endl;
// }


// template <class Container = std::vector<int> >
// const Container& get_unvisited_vertices(
// 		const Container& vertices,
// 		const Container& order_list)
// {
// 	Container unvisited_vertices;

// 	for (auto vertex : vertices)
// 		if (order_list.find(vertex)
// 			== order_list.end())
// 			unvisited_vertices.push_back(vertex);

// 	return unvisited_vertices;
// }


// template <
// 		class Graph,
// 		class VertexType = int,
// 		class Container = std::vector<VertexType>,
// 		typename Function>
// void walk_dfs(
// 		const Graph& graph,
// 		const VertexType& vertex,
// 		Container& visited_list = {},
// 		Function f = show_vertex)
// {
// 	const Container& unvisited_vertices = get_unvisited_vertices(
// 			graph.get_nearest(vertex),
// 			visited_list);

// 	for (auto v : unvisited_vertices)
// 	{
// 		visited_list.push_back(v);
// 		walk_dfw(graph, v, visited_list, f);
// 	}

// 	f(vertex);
// }
