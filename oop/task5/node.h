#ifndef __NODE_H__
#define __NODE_H__


#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;


static const string DEFINITION_SYMBOL = " = ";
static const string DEFINITION_SEPARATOR = ", ";


// Class //

class Node : public list<string>
{
	public:
		// Constructors / Destructor.
		Node()
			: list<string>() {}
		Node(const list<string> &node)
			: list<string>(node) {}

		// Getters.
		iterator find(const string &data);
		const_iterator find(const string &data) const;

		iterator rfind(const string &data);
		const_iterator rfind(const string &data) const;

		bool has_subnode(const Node &node) const;
		bool is_looped() const;
		bool is_head_equals(const Node &node) const { return (front() == node.front()); }

		// Methods.
		bool subinsert(const iterator &pos, const Node &node);

		// Operators.
		bool operator==(const Node &node) const;
		bool operator!=(const Node &node) const;

		// Friend.
		friend ostream &operator<<(ostream &out, const Node &node);
};

ostream &operator<<(ostream &out, const Node &node);


// Functions //
Node subconnect_nodes(const vector<Node> &nodes);
void bubble_sort_nodes(vector<Node> &nodes);


// Extra functions //
Node read_node_from_file(const string &filename);
vector<Node> read_definitions_from_file(const string &filename);
list<string> split(const string &s, const string &separator);


// __NODE_H__
#endif
