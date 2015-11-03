#include <iostream>
using namespace std;

#include "argvparser.h"


class DataStruct
{
	public:
		DataStruct() {}
		int i;
		int t;
		string s;
};


//ParserAction helpmsg(const ArgvFlag&, DataStruct&)
//{
//	cout << "Help message" << endl;
//}


int main(int argc, char **argv)
{
	ArgvParser<DataStruct> parser;

//	parser.register_flag_parser("--help", helpmsg);
	parser.set_arguments(argc, argv);
	parser.parse_input();

	DataStruct input = parser.get_parsed_data();
	cout << parser.is_input_valid() << endl;
	return 0;
}

