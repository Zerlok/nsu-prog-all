#ifndef __GRAPHWALKER_H__
#define __GRAPHWALKER_H__


template <class VertexType>
void show_vertex(const VertexType& v)
{
	std::cout << v << std::endl;
}


template <class Container>
Container get_unvisited_vertices(
		const Container& old_list,
		const Container& order_list,
		const Container& neighbours)
{
	Container unvisited_vertices(old_list);

	for (auto vertex : vertices)
		if ((std::find(order_list.begin(), order_list.end(), vertex) == order_list.end())
			&& (unvisited_vertices))
			unvisited_vertices.push_back(vertex);

	return unvisited_vertices;
}



template <
		class Graph,
		class VertexType>
void walk_dfs(
		const Graph& graph,
		const VertexType& vertex)
{
	// std::vector<VertexType> neighbours = ;
	std::vector<VertexType> visited = {};
	VertexType v = vertex;
	visited.push_back(vertex);
	std::vector<VertexType> unvisited = get_unvisited_vertices(graph.get_nearest(vertex), visited);
	
	while (!unvisited.empty())
	{
		v = unvisited.back();
		unvisited.pop_back();

		if (std::find(visited.begin(), visited.end(), v)
			== visited.end())
		{
			visited.push_back(v);
			std::cout << v << std::endl;
		}

		unvisited = get_unvisited_vertices(
				unvisited,
				visited,
				graph.get_nearest(v));
	}
	
	std::cout << vertex << std::endl;
}


// _GRAPHWALKER_H__
#endif
