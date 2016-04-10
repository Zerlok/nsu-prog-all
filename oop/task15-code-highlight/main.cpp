#include <iostream>
#include <fstream>
#include "decorators.h"


int main(int argc, char *argv[])
{
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);

	Decorator* main = new HTMLDecorator(
			new KeywordsHighlightDecorator(
			new LineNumbersDecorator()));

	main->execute(in, out);

	delete main;
	return 0;
}
