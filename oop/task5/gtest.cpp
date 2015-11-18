#include <algorithm>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "node.h"


// -------------------------- EXTRA --------------------------//

static const string INPUT_FILE_TAIL = "-input.txt";
static const string OUTPUT_FILE_TAIL = "-output.txt";


bool operator==(const vector<Node> &node1, const vector<Node> &node2)
{
	size_t len = node1.size();

	if (len != node2.size())
		return false;

	for (size_t i = 0; i < len; ++i)
		if (node1[i] != node2[i])
			return false;

	return true;
}


bool operator!=(const vector<Node> &node1, const vector<Node> &node2)
{
	return !(operator==(node1, node2));
}


// -------------------------- NODE --------------------------//
TEST(Node, Init)
{
	ASSERT_NO_THROW({
		Node();
		Node(list<string>({"a", "b", "c"}));
		Node({"a", "b", "c"});
	});
}


TEST(Node, OpertorEqNeq)
{
	const vector<Node> a = {
		Node(),
		Node({"3", "2", "1"}),
		Node({"aaa", "bbb", "ccc"})
	};
	const vector<Node> b = {
		Node(list<string>()),
		Node(list<string>({"3", "2", "1"})),
		Node(list<string>({"aaa", "bbb", "ccc"}))
	};
	const vector<Node> c = {
		Node({"a"}),
		Node({"1", "2", "3"}),
		Node({"aaa", "0", "1"})
	};

	EXPECT_EQ(a, b);
	EXPECT_NE(b, c);
}


TEST(Node, Find)
{
	const vector<Node> nodes = {
		Node({"0", "1", "2", "3"}),
		Node({"aaa", "bbb", "ccc"}),
		Node({"def", "desc1", "desc2", "desc3", "desc4"})
	};
	const vector<string> valid_searches = {
		"2",
		"ccc",
		"def"
	};
	const vector<string> invalid_searches = {
		"12",
		"a",
		"desc0"
	};

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		Node::const_iterator end = nodes[i].cend();
		EXPECT_EQ(end, nodes[i].find(invalid_searches[i]));
		EXPECT_NE(end, nodes[i].find(valid_searches[i]));
	}
}


TEST(Node, EmptyNode)
{
	Node node = Node({"#", "*"});
	Node empty_node = Node();

	EXPECT_TRUE(empty_node.empty());
	EXPECT_TRUE(empty_node.has_subnode(Node()));
	EXPECT_EQ(empty_node.end(), empty_node.begin());
	EXPECT_EQ(empty_node.end(), empty_node.find("*"));

	EXPECT_TRUE(empty_node.replace(empty_node.begin(), node));
	EXPECT_FALSE(empty_node.empty());
	EXPECT_NE(empty_node.end(), empty_node.find("*"));
	EXPECT_TRUE(empty_node.has_subnode(Node()));
}


TEST(Node, Replace)
{
	vector<Node> a = {
		Node({"*"}),
		Node({"1", "two"}),
		Node({"one", "2", "3"}),
		Node({"0", "1", "dtwo", "3", "4"}),
	};
	const vector<Node> b = {
		Node({"*"}),
		Node({"two", "2", "3", "4"}),
		Node({"one", "-1", "0", "1"}),
		Node({"dtwo", "2.00", "2.33", "2.66"}),
	};
	const vector<Node> c = {
		Node(),
		Node({"1", "2", "3", "4"}),
		Node({"-1", "0", "1", "2", "3"}),
		Node({"0", "1", "2.00", "2.33", "2.66", "3", "4"}),
	};

	for (size_t i = 0; i < a.size(); ++i)
	{
		Node::iterator it = a[i].find(b[i].front());
		a[i].replace(it, b[i]);
		EXPECT_EQ(c[i], a[i]);
	}
}


TEST(Node, Subnode)
{
	const vector<Node> nodes = {
		Node(),
		Node({"1", "2"}),
		Node({"1", "2", "3"}),
		Node({"0", "1", "2", "3", "4"}),
		Node({"ccc", "aaa", "bbb"}),
		Node({"*"})
	};
	const vector<Node> valid_subnodes = {
		Node(),
		Node({"2", "3", "4"}),
		Node({"1", "0", "-1"}),
		Node({"2", "2.00", "2.33", "2.66"}),
		Node({"aaa"}),
		Node()
	};
	const vector<Node> invalid_subnodes = {
		Node({"*"}),
		Node({"3", "4"}),
		Node({"0", "1"}),
		Node({"digits", "1", "2", "3"}),
		Node({"a"}),
		Node({"__", "*"})
	};

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		EXPECT_TRUE(nodes[i].has_subnode(nodes[i]));

		EXPECT_TRUE(nodes[i].has_subnode(valid_subnodes[i]))
				<< "actualy: " << valid_subnodes[i] << " !> " << nodes[i];
		EXPECT_FALSE(nodes[i].has_subnode(invalid_subnodes[i]))
				<< "actualy: " << invalid_subnodes[i] << " >> " << nodes[i];
	}
}


TEST(Node, Subconnecting)
{

}


// -------------------------- ALGORYTHM --------------------------//
TEST(Algorythm, TestFiles)
{
	const std::vector<std::string> casenames = {
		"test01",
		"test02",
		"test03",
//		"test04"
	};

	for (const std::string &casename : casenames)
	{
		string input_name = casename;
		string output_name = casename;
		input_name += INPUT_FILE_TAIL;
		output_name += OUTPUT_FILE_TAIL;

		std::vector<Node> nodes = read_definitions_from_file(input_name);
		std::sort(nodes.begin(), nodes.end(), compare_nodes);
		Node algorythm_result = subconnect_nodes(nodes);

		EXPECT_EQ(read_node_from_file(output_name), algorythm_result);
	}
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
