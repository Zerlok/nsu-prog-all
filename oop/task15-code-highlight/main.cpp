#include <iostream>
#include <fstream>
#include "decorators.h"


int main(int argc, char *argv[])
{
	std::ifstream in;
	std::ofstream out;

	Decorator* main = new HTMLDecorator(
			new KeywordsHighlightDecorator(
			new LineNumbersDecorator(
			new StringHighlightDecorator())));

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
