#ifndef __GRAPHWALKER_H__
#define __GRAPHWALKER_H__


template <class VertexType>
void show_vertex(const VertexType& v)
{
	std::cout << v << std::endl;
}


template <class Container>
const Container get_unvisited_vertices(
		const Container& vertices,
		const Container& order_list)
{
	Container unvisited_vertices;

	for (auto vertex : vertices)
		if (std::find(order_list.begin(), order_list.end(), vertex)
			== order_list.end())
			unvisited_vertices.push_back(vertex);

	return unvisited_vertices;
}



template <
		class Graph,
		class VertexType,
		class Container>
void walk_dfs(
		const Graph& graph,
		const VertexType& vertex,
		Container& visited_list)
{
	if (std::find(visited_list.begin(), visited_list.end(), vertex) == visited_list.end())
	{
		visited_list.push_back(vertex);

		const Container unvisited_vertices = get_unvisited_vertices(
				graph.get_nearest(vertex),
				visited_list);

		// std::cout << "{\n"
		// 		<< "        num: " << vertex << "\n"
		// 		<< "     nearby: " << graph.get_nearest(vertex) << "\n"
		// 		<< "    visited: " << visited_list << "\n"
		// 		<< "  unvisited: " << get_unvisited_vertices(graph.get_nearest(vertex), visited_list) << "\n}"
		// 		<< std::endl;

		for (auto v : unvisited_vertices)
			walk_dfs<Graph, VertexType, Container>(graph, v, visited_list);
			// visited_list.push_back(v);
		
		std::cout << vertex << std::endl;
	}
}


// _GRAPHWALKER_H__
#endif