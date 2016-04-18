#include <iostream>
#include <fstream>
#include "decorators.h"


int main(int argc, char *argv[])
{
	std::ifstream in;
	std::ofstream out;

	HTMLComponent data;

	HTMLDecorator decorator;
	CodeToHTMLDecorator code_to_html;
	KeywordsHighlightDecorator keywords_highlighter;
	LineNumbersDecorator line_numerator;
	StringHighlightDecorator string_highlighter;
	CommentHighlightDecorator comment_highlighter;

	decorator
			<< line_numerator
			<< code_to_html
			<< string_highlighter
			<< keywords_highlighter
			<< comment_highlighter;

	data.add_style("\
			font, pre { font-family: Ubuntu Mono, Monospace; } \
			pre { -moz-tab-size: 4; tab-size: 4;} \
	");
	decorator.add_style(data);

	if (argc < 2)
		std::cerr << "At least one argument is required: file for parsing." << std::endl
				  << "Second argument is output html file (optional)." << std::endl;

	else if (argc == 2)
	{
		in.open(argv[1]);
		in >> data;
		decorator.execute(data);
		std::cout << data << std::endl;
	}

	else if (argc == 3)
	{
		in.open(argv[1]);
		in >> data;
		decorator.execute(data);
		out.open(argv[2]);
		out << data << std::endl;
	}

	return 0;
}
