#include <iostream>
#include <fstream>
#include "editor.h"


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		Editor string_editor(std::cin, std::cout);
		string_editor.run();
	}

	else if (argc == 3)
	{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);

		Editor string_editor(in, out);
		string_editor.run();
	}

	else
	{
		std::cout << "Simple string editor by zerlok." << std::endl;
		std::cout << "Usage: " << argv[0] << "[INPUT] [OUTPUT]" << std::endl;
		std::cout << "If input and output file is not specified, chooses std input and output streams." << std::endl;
	}

	return 0;
}

