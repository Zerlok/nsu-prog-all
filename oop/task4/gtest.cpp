#include <iostream>
#include <gtest/gtest.h>

#include "graph.h"
#include "treebuilder.h"


TEST(Vertex, Init)
{
	ASSERT_NO_THROW({
			Vertex();
			Vertex(0, 1);
			Vertex(2, 3, 4);
			Vertex(5, 6, 7, 8);
	});
}


TEST(Vertex, Distance)
{
	const int n = 5;
	const Vertex center(1, 1);
	const Vertex vertices[n] = {
		Vertex(1, 1),
		Vertex(1, 11),
		Vertex(-9, 1),
		Vertex(-3, 4),
		Vertex(4, 5)
	};
	const double distances[n] = {
		0.0, 10.0, 10.0, 5.0, 5.0
	};

	for (int i = 0; i < n; ++i)
	{
		EXPECT_EQ(distances[i], distance(center, vertices[i]));
		EXPECT_EQ(distances[i], distance(vertices[i], center));
	}
}


TEST(Vertex, OperatorEqEq)
{
	const vector<Vertex> a = {
		Vertex(0, 0),
		Vertex(0, 1, -1),
		Vertex(1, 0, 1),
		Vertex(1, 1, 3, 1),
		Vertex(0, 1, -2, -10)
	};
	const vector<Vertex> b = {
		Vertex(1, 1, 0),
		Vertex(10, 11, -1),
		Vertex(-1, 0, 1),
		Vertex(1, 3, 3, 4),
		Vertex(0, 1, -2, 3)
	};

	for (int i = 0; i < a.size(); ++i)
		EXPECT_EQ(a[i], b[i]);
}


TEST(Vertex, OperatorNeq)
{
	const vector<Vertex> a = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 0),
		Vertex(1, 1),
		Vertex(0, 1, 2)
	};
	const vector<Vertex> b = {
		Vertex(0, 0, -1),
		Vertex(0, 1, 10),
		Vertex(1, 0, 1),
		Vertex(1, 1, 2),
		Vertex(0, 1, -2)
	};

	for (int i = 0; i < a.size(); ++i)
		EXPECT_NE(a[i], b[i]);
}


TEST(Vertex, OperatorLt)
{
	const vector<Vertex> a = {
		Vertex(0, 100, -1),
		Vertex(10, 11),
		Vertex(1, 0, 2),
		Vertex(1, 1, -5),
		Vertex(0, 1, -2)
	};
	const vector<Vertex> b = {
		Vertex(0, 0),
		Vertex(0, 1, 1),
		Vertex(1, 0, 10),
		Vertex(0, 0, -3),
		Vertex(-2, -1, 55)
	};

	for (int i = 0; i < a.size(); ++i)
		EXPECT_LT(a[i], b[i]);
}


TEST(Vertex, Swap)
{
	vector<Vertex> a = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 0),
		Vertex(1, 1),
		Vertex(0, 1, 2)
	};
	vector<Vertex> b = {
		Vertex(0, 0, -1),
		Vertex(0, 1, 10),
		Vertex(1, 0, 1),
		Vertex(1, 1, 2),
		Vertex(0, -1, 0)
	};
	const vector<Vertex> c = {
		Vertex(0, 0, -1),
		Vertex(0, -1, 10),
		Vertex(1, 100, 1),
		Vertex(-6, 5, 2),
		Vertex(0, 1)
	};

	for (int i = 0; i < a.size(); ++i)
		a[i].swap(b[i]);

	for (int i = 0; i < c.size(); ++i)
		EXPECT_EQ(a[i], c[i]);
}


TEST(Graph, Init)
{
	const vector<Vertex> vertices = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 0),
		Vertex(1, 1)
	};

	ASSERT_NO_THROW({
			Graph();
			Graph(vertices);
	});
}


TEST(Graph, BracketsOperator)
{
	const vector<Vertex> vertices = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 0),
		Vertex(1, 1)
	};

	Graph g(vertices);
	EXPECT_EQ(vertices[0], g[0]);

	for (int i = 1; i < vertices.size(); ++i)
		EXPECT_NE(vertices[i], g[i]);

	EXPECT_EQ(Vertex::none, g[-12]);
	EXPECT_EQ(Vertex::none, g[1000]);
}


TEST(Graph, AddVertex)
{
	const vector<Vertex> vertices = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 0),
		Vertex(1, 1)
	};

	Graph g(vertices);

	// with 0
	EXPECT_TRUE(g.connect(g[0], g[1]));
	EXPECT_TRUE(g.connect(g[2], g[0]));
	EXPECT_TRUE(g.connect(g[0], g[3]));
	EXPECT_FALSE(g.connect(g[0], g[1]));

	// with 1
	EXPECT_TRUE(g.connect(g[1], g[3]));
	EXPECT_TRUE(g.connect(g[2], g[1]));
	EXPECT_FALSE(g.connect(g[1], g[3]));

	// with 2
	EXPECT_TRUE(g.connect(g[2], g[3]));
}


TEST(Graph, EmptyGraph)
{
	Graph g = Graph();

	EXPECT_EQ(Vertex::none, g[0]);
	EXPECT_EQ(0, g.get_vertices().size());
	EXPECT_EQ(0, g.get_edges().size());

	EXPECT_FALSE(g.has_vertex(0));
	EXPECT_FALSE(g.has_vertex(g[0]));
	EXPECT_FALSE(g.has_edge(g[0], g[1]));
}


TEST(Graph, IsolatedGraph)
{
	const int num = 10;
	Graph g = Graph(Graph::t_vertices(num));

	for (int i = 0; i < num; ++i)
		EXPECT_NE(Vertex::none, g[i]);

	EXPECT_EQ(Vertex::none, g[num]);
	EXPECT_EQ(10, g.get_vertices().size());
	EXPECT_EQ(0, g.get_edges().size());

	EXPECT_FALSE(g.has_vertex(num));
	EXPECT_FALSE(g.has_vertex(g[num]));

	for (const Vertex &v : g.get_vertices())
		for (const Vertex &u : g.get_vertices())
			EXPECT_FALSE(g.has_edge(v, u));
}


TEST(Algorythm, Case1)
{
	Graph g({
		Vertex(7, 5),
		Vertex(3, -11),
		Vertex(2, -2),
		Vertex(-1, -8),
		Vertex(14, -14)
	});
	vector<Vertex::t_num_pair> connections = {{0, 2}, {1, 3}, {1, 4}, {2, 3}};

	build_tree(g);

	EXPECT_TRUE(equals_as_sets(g.get_connections(), connections));
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
