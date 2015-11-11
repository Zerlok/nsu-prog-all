#include "node.h"


const Node Node::none = Node();
const Node::Iterator Node::Iterator::none = Iterator(nullptr);


Node::Node()
	: _next(nullptr),
	  _previous(nullptr),
	  _data()
{
}


Node::Node(const string &data)
	: _next(nullptr),
	  _previous(nullptr),
	  _data(data)
{
}


Node::Node(const vector<string> &data)
	: _next(nullptr),
	  _previous(nullptr),
	  _data(data[0])
{
	vector<Node *> nodes;

	for (const string &d : data)
		nodes.push_back(new Node(d));

	for (size_t i = 1; i < nodes.size(); ++i)
	{
		Node *node_i = nodes[i];
		node_i->_previous = nodes[i-1];
		node_i->_previous->_next = node_i;
	}
}


Node::~Node()
{
	delete _next;
}


Node::Iterator Node::begin()
{
	if (_previous == nullptr)
		return Iterator(this);

	Iterator b;
	for (Iterator it = Iterator(this->_previous);
		  it != Iterator::none;
		 --it)
		b = it;

	return b;
}


Node::Iterator Node::end()
{
	if (_next == nullptr)
		return Iterator(this);

	Iterator e;
	for (Iterator it = Iterator(_next);
		  it != Iterator::none;
		 ++it)
		e = it;

	return e;
}


const Node::Iterator Node::begin() const
{
	if (_previous == nullptr)
		return Iterator(this);

	Iterator b;
	for (Iterator it = Iterator(_previous);
		  it != Iterator::none;
		 --it)
		b = it;

	return b;
}


//const Node::Iterator Node::end()
//{
//	if (_next == nullptr)
//		return Iterator(this);

//	Iterator e;
//	for (const Iterator it = Iterator(_next);
//		  it != Iterator::none;
//		 ++it)
//		e = it;

//	return e;
//}


Node::Iterator Node::find(const Node &subnode)
{
	for (Iterator it = begin();
		 it != Iterator::none;
		 ++it)
		if (it.reference() == subnode)
			return it;

	return Iterator::none;
}


bool Node::insert(Iterator &it, Node *node)
{
	if (it == Iterator::none)
		return false;

	Node *first = node->begin().pointer();
	Node *last = node->end().pointer();

	it->_previous = first;
	last->_next = it->_next;
	last->_next->_previous = last;

	return true;
}


istream &operator>>(istream &in, Node &node)
{
	in >> node._data;
	return in;
}


ostream &operator<<(ostream &out, Node &node)
{
	out << "[";

	for (Node::Iterator it = node.begin();
		 it != Node::Iterator::none;
		 ++it)
		out << "'" << (*it)._data << "' ";

	out << "]" << endl;

	return out;
}
