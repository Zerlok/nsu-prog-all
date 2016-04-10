#include <iostream>
#include <fstream>
#include "decorators.h"


int main(int argc, char *argv[])
{
	std::ifstream in(argv[1]);

	Decorator* main = new HTMLDecorator(
			new LineNumbersDecorator(
			new KeywordsHighlightDecorator()));

	main->execute(in, std::cout);
	std::cout << std::endl;

	delete main;
	return 0;
}
