#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

#include "node.h"


static const char *NODE_SEPARATOR = "\n";


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "One argument required: name of file with definitions." << endl;
		return 1;
	}

	vector<Node> nodes = read_definitions_from_file(argv[1]);

	sort(nodes.begin(), nodes.end(), compare_nodes);

	Node result = subconnect_nodes(nodes);
	copy(result.begin(), result.end(), ostream_iterator<Node::value_type>(cout, NODE_SEPARATOR));
	cout << endl;

	return 0;
}

