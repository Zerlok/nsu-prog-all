#include <iostream>
#include <fstream>
#include "decorators.h"


int main(int argc, char *argv[])
{
	std::ifstream in;
	std::ofstream out;

	HTMLComponent data;
	data.add_style("\
			pre {-moz-tab-size: 4; tab-size: 4;} \
			div, font {font-family: Ubuntu Mono, Monospace; } \
			div {display: inline-block; } \
			div.line {width: 100%; } \
			div.line:hover {background: #EAEAEA; } \
			div.linenum {text-align: right; width: 35px; color: #808080; margin-right: 10px; } \
			font.macros, font.basetype, font.baseword {font-weight: bold; } \
			font.macros {color: #909090; } \
			font.basetype {font-style: italic; } \
			font.comment {color: #A0A0A0; font-style: italic; } \
			font.string {color: #A0A050; } \
	");

	CodeToHTMLDecorator code_to_html;
	KeywordsHighlightDecorator keywords_highlighter;
	LineNumbersDecorator line_numerator;
	StringHighlightDecorator string_highlighter;

	code_to_html
			<< string_highlighter
			<< keywords_highlighter
			<< line_numerator;

	if (argc < 2)
		std::cerr << "At least one argument is required: file for parsing." << std::endl
				  << "Second argument is output html file (optional)." << std::endl;

	else if (argc == 2)
	{
		in.open(argv[1]);
		in >> data;
		code_to_html.execute(data);
		std::cout << data << std::endl;
	}

	else if (argc == 3)
	{
		in.open(argv[1]);
		in >> data;
		code_to_html.execute(data);
		out.open(argv[2]);
		out << data << std::endl;
	}

	return 0;
}
