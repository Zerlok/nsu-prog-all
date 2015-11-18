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


bool Node::replace(const Node::iterator &pos, const Node &node)
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
	Node sorted;
	sorted.push_back(nodes.front().front());

	Node::iterator node_head_pos;

	for (const Node &node : nodes)
	{
		for (node_head_pos = sorted.find(node.front());
			 node_head_pos != sorted.end();
			 node_head_pos = sorted.find(node.front()))
			sorted.replace(node_head_pos, node);
	}

	return sorted;
}


bool compare_nodes(const Node &node, const Node &subnode)
{
	return node.has_subnode(subnode);
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
			ss << "Looped definition found: " << node;
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
