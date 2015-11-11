#ifndef __NODE_H__
#define __NODE_H__


#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;


class Node
{
	public:
		// Static.
		static const Node none;

		// Constructor / Destructor.
		Node();
		Node(const string &data);
		Node(const vector<string> &data);
		~Node();

		// Iterators.
		class Iterator
		{
			public:
				// Static.
				static const Iterator none;

				// Constructors / Destructor.
				Iterator()
					: _ptr(nullptr) {}
				Iterator(const Node *node)
					: _ptr(node) {}
				Iterator(const Iterator &it)
					: _ptr(it._ptr) {}
				~Iterator() {}

				// Getters.
				bool is_null() const { return (_ptr == nullptr); }
				Node &reference() { return (*_ptr); }
				Node *pointer() { return _ptr; }
				const Node &reference() const { return (*_ptr); }
				const Node *pointer() const { return _ptr; }

				// Operators.
				Node &operator*() { return reference(); }
				Node *operator->() { return pointer(); }
				const Node &operator*() const { return reference(); }
				const Node *operator->() const { return pointer(); }

				Iterator &operator=(const Iterator &it)
				{
					_ptr = it._ptr;
					return (*this);
				}

				Iterator &operator++()
				{
					_ptr = _ptr->_next;
					return (*this);
				}
				Iterator &operator++(int)
				{
					Iterator curr = Iterator(*this);
					++_ptr;
					return curr;
				}

				Iterator &operator--()
				{
					_ptr = _ptr->_previous;
					return (*this);
				}
				Iterator &operator--(int)
				{
					Iterator curr = Iterator(*this);
					--_ptr;
					return curr;
				}

				bool operator==(const Iterator &it) const { return (_ptr == it._ptr); }
				bool operator!=(const Iterator &it) const { return (_ptr != it._ptr); }

			private:
				// Fields.
				Node *_ptr;
		};

		

		// Getters.
		const string &get_data() const { return _data; }

		Iterator begin();
		Iterator end();
		const ConstIterator begin() const;
		const ConstIterator end() const;

		Node &head() { return begin().reference(); }
		Node &tail() { return end().reference(); }
		const Node &head() const { return begin().reference(); }
		const Node &tail() const { return end().reference(); }

		// Methods.
		Iterator find(const Node &subnode);
		const Iterator find(const Node &subnode) const;
		bool insert(Iterator &it, Node *node);

		// Operators.
		bool operator==(const Node &node) const { return _data == node._data; }
		bool operator!=(const Node &node) const { return _data != node._data; }
		friend istream &operator>>(istream &in, Node &node);
		friend ostream &operator<<(ostream &out, Node &node);

	private:
		// Fields.
		Node *_next;
		Node *_previous;

		string _data;
};


istream &operator>>(istream &in, Node &node);


// __NODE_H__
#endif
