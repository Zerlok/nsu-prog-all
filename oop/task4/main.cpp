#include <iostream>
#include <set>
using namespace std;

#include "../argvparser.h"


class Vertex
{
	public:
		Vertex(int x, int y) : _x(x), _y(y) {}
		Vertex(const Vertex &v) : _x(v._x), _y(v._y) {}

		bool operator==(const Vertex &v) { return ((_x == v._x)
												   && (_y == v._y)); }

		Vertex &operator=(const Vertex &v)
		{
			_x = v._x;
			_y = v._y;

			return (*this);
		}

		int _x;
		int _y;
};


int main(int argc, char *argv[])
{
	Vertex v1 =	Vertex(100, 100);
	set<Vertex*> vertices = {
		new Vertex(0, 1),
		new Vertex(2, 3),
		new Vertex(-1, -1)
	};

	for (auto const v : vertices)
		cout << "(" << v->_x << " " << v->_y << ")" << endl;

	vertices.insert(&v1);

	v1._x = -100;

	for (auto const v : vertices)
		cout << "(" << v->_x << " " << v->_y << ")" << endl;

	return 0;
}

