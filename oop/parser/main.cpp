#include <iostream>
using namespace std;

#include "argvparser.h"


typedef struct Data
{
	int i;
	int t;
	string s;
} Data;


class D
{
	public:
		D() {}
};


int main(int argc, char **argv)
{
	ArgvParser<D> parser;

	parser.set_arguments(argc, argv);

	cout << "Hello World!" << endl;
	return 0;
}

