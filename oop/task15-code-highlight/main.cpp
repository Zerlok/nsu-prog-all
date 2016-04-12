#include <iostream>
#include <fstream>
#include "decorators.h"


//void insert(std::stringstream& ss, const size_t& pos, const std::string& s)
//{
//	const size_t size = s.size();
//	char tmp[size];
//	std::streampos out_pos = ss.tellp();
//	ss.seekg(pos);
//	ss.get(tmp, size);

//	ss.seekp(pos);
//	ss << s;
//	ss.seekg(pos + s.size());
//	std::cout << "ss: '" << ss.str() << std::endl;
////	ss.seekp(out_pos + s.size());
//	ss.seekp(out_pos);
//}


int main(int argc, char *argv[])
{
	std::ifstream in;
	std::ofstream out;

	Decorator* main = new HTMLDecorator(
			new StringHighlightDecorator(
			new KeywordsHighlightDecorator(
			new LineNumbersDecorator(
	))));

	if (argc < 2)
		std::cerr << "At least one argument is required: file for parsing." << std::endl
				  << "Second argument is output html file (optional)." << std::endl;

	else if (argc == 2)
	{
		in.open(argv[1]);
		main->execute(in, std::cout);
	}

	else if (argc == 3)
	{
		in.open(argv[1]);
		out.open(argv[2]);
		main->execute(in, out);
	}

	delete main;

	return 0;
}
