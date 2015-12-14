#include <iostream>
#include "datapackage.h"
using namespace std;


int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;

	for (int i = 1; i < argc; ++i)
		cout << argv[i] << " : " << DataPackage(argv[i]) << endl;

	return 0;
}

