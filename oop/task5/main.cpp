#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <algorithm>
using namespace std;


//const list<Node> read_nodes(const string &filename)
//{
//	ifstream input(filename);

//	if (!input.is_open())
//	{
//		stringstream ss;
//		ss << "Cannot read the file: " << filename;
//		throw invalid_argument(ss.str());
//	}

//	list<Node> nodes;
//	copy(istream_iterator<Node>(input),
//			  istream_iterator<Node>(),
//			  back_inserter(nodes));

//	input.close();
//	return nodes;
//}


list<string> split(const string &s, const string &delim)
{
	string data(s);
	list<string> splitted_string;

	for (string::size_type delim_pos = data.find(delim);
		 delim_pos != string::npos;
		 delim_pos = data.find(delim))
	{
		splitted_string.push_back(data.substr(0, delim_pos));
		data = data.substr(delim_pos + delim.length());
	}

	splitted_string.push_back(data);

	return splitted_string;
}


int main()
{
	string line;
	string::size_type eq_pos;
	list<string> data;
	list<string> data_description;
	ifstream input("test01-input.txt");

	while (getline(input, line))
	{
		eq_pos = line.find(" = ");
		data_description = split(line.substr(eq_pos + 3), ", ");
		data.push_back(line.substr(0, eq_pos));
		data.insert(data.end(), data_description.begin(), data_description.end());

		cout << "[";
		for (const string &s : data)
			cout << s << "|";

		cout << "]" << endl;

		data.clear();
	}

	return 0;
}

