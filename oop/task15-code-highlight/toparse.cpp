stringutils::search_replace_all(line, "<", "&lt;");

#include <iostream>
#include <fstream>
#include "decorators.h"

using __my_int__ = int;


class Decorator
{
	public:
		Decorator()
			: _inner(nullptr) {}
		Decorator(Decorator* inner)
			: _inner(inner) {}
		virtual ~Decorator();

		virtual void execute(std::istream& in, std::ostream& out);

	protected:
		Decorator* _inner;
};


int main(int argc, char *argv[])
{
	std::string s;
	s = "\""; // ololo.
	s = "//"; // kokoko
	std::ifstream in;
	std::ofstream out;

//	Decorator* main = new HTMLDecorator(new StringHighlightDecorator());
	Decorator* main = new HTMLDecorator(
			new KeywordsHighlightDecorator(
			new LineNumbersDecorator()));

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
