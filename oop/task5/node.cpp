#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iterator>
using namespace std;

#include "node.h"


// -------------------------- CLASS NODE --------------------------//

Node::iterator Node::find(const string &data)
{
	Node::iterator it;

	for (it = begin();
		 it != end();
		 ++it)
		if (data.compare(*it) == 0)
			break;

	return it;
}


Node::const_iterator Node::find(const string &data) const
{
	Node::const_iterator cit;

	for (cit = cbegin();
		 cit != cend();
		 ++cit)
		if (data.compare(*cit) == 0)
			break;

	return cit;
}


Node::iterator Node::rfind(const string &data)
{
	Node::iterator it;

	for (it = end();
		 it != begin();
		 --it)
		if (data.compare(*it) == 0)
			break;

	return it;
}


Node::const_iterator Node::rfind(const string &data) const
{
	Node::const_iterator it;

	for (it = cend();
		 it != cbegin();
		 --it)
		if (data.compare(*it) == 0)
			break;

	return it;
}


bool Node::subinsert(const Node::iterator &pos, const Node &node)
{
	this->insert(
			pos,
			++(node.begin()),
			node.end()
	);

	if (pos != end())
		this->erase(pos);

	return true;
}


bool Node::has_subnode(const Node &node) const
{
	if (node.empty())
		return true;

	if (empty())
		return false;

	return (find(node.front()) != end());
}


bool Node::is_looped() const
{
	return (rfind(front()) != begin());
}


bool Node::operator==(const Node &node) const
{
	Node::const_iterator it = cbegin();
	Node::const_iterator node_it = node.cbegin();

	while ((it != cend())
		   && (node_it != node.cend()))
	{
		if ((*it).compare(*node_it) != 0)
			return false;

		++it;
		++node_it;
	}

	return ((it == cend())
			&& (node_it == node.cend()));
}


bool Node::operator!=(const Node &node) const
{
	return !(this->operator==(node));
}


ostream &operator<<(ostream &out, const Node &node)
{
	out << "[";

	for (const string &data : node)
		out << "'" << data << "' ";

	out << "]";

	return out;
}



// -------------------------- FUNCTIONS --------------------------//

Node subconnect_nodes(const vector<Node> &nodes)
{
	Node linked;
	if (nodes.empty()
			|| nodes.front().empty())
		return linked;

	const string &main_head = nodes.front().front();
	linked.push_back(main_head);

	for (const Node &node : nodes)
	{
		if (node.empty())
			continue;

		const string &node_head = node.front();
		for (Node::iterator node_head_pos = linked.find(node_head);
			 node_head_pos != linked.end();
			 node_head_pos = linked.find(node_head))
			linked.subinsert(node_head_pos, node);

		if (linked.find(main_head) != linked.cend())
		{
			stringstream ss;
			ss << "Looped definition found during node subconnecting: " << linked
			   << " (value: '" << main_head << "'), execution stopped.";
			throw invalid_argument(ss.str());
		}
	}

	return linked;
}


void bubble_sort_nodes(vector<Node> &nodes)
{
	size_t len = nodes.size();
	for (size_t i = 0; i < len; ++i)
		for (size_t j = i + 1; j < len; ++j)
			if (nodes[j].has_subnode(nodes[i]))
				nodes[j].swap(nodes[i]);
}


Node read_node_from_file(const string &filename)
{
	ifstream input(filename);

	if (!input.is_open())
	{
		stringstream ss;
		ss << "Cannot read the file: " << filename;
		throw invalid_argument(ss.str());
	}

	string line;
	Node node;

	input >> noskipws;
	while (getline(input, line))
		node.push_back(line);

	input.close();

	return node;
}


vector<Node> read_definitions_from_file(const string &filename)
{
	ifstream input(filename);

	if (!input.is_open())
	{
		stringstream ss;
		ss << "Cannot read the file: " << filename;
		throw invalid_argument(ss.str());
	}

	string line;
	string::size_type def_pos;
	vector<Node> data;

	while (getline(input, line))
	{
		if (line.empty())
			continue;

		Node node;
		Node definition;

		def_pos = line.find(DEFINITION_SYMBOL);
		definition = split(
				line.substr(def_pos + DEFINITION_SYMBOL.length()),
				DEFINITION_SEPARATOR
		);
		node.push_back(line.substr(0, def_pos));
		node.insert(
				node.end(),
				definition.begin(),
				definition.end()
		);

		if (node.is_looped())
		{
			stringstream ss;
			ss << "Looped definition found: " << node
			   << " (value: '" << node.front() << "'), execution stopped.";
			throw invalid_argument(ss.str());
		}

		data.push_back(node);
	}

	input.close();

	return data;
}


list<string> split(const string &s, const string &separator)
{
	string data(s);
	list<string> splitted_string;

	for (string::size_type separator_pos = data.find(separator);
		 separator_pos != string::npos;
		 separator_pos = data.find(separator))
	{
		splitted_string.push_back(data.substr(0, separator_pos));
		data = data.substr(separator_pos + separator.length());
	}

	splitted_string.push_back(data);

	return splitted_string;
}
