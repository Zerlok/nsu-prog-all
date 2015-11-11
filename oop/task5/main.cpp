#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <iterator>
#include <algorithm>
using namespace std;

#include "node.h"


const vector<Node> read_nodes(const string &filename)
{
	ifstream input(filename);

	if (!input.is_open())
	{
		stringstream ss;
		ss << "Cannot read the file: " << filename;
		throw invalid_argument(ss.str());
	}

	vector<Node> nodes;
	copy(istream_iterator<Node>(input),
			  istream_iterator<Node>(),
			  back_inserter(nodes));

	input.close();
	return nodes;
}


int main()
{
	char c;
	string str;
	ifstream input("test01-input.txt");

	while (getline(input, str))
	{
		istringstream ss(str);

		while (ss >> c)
			cout << c << " ";

		cout << endl;
	}

	return 0;
}

