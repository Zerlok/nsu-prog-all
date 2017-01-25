#include <gtest/gtest.h>
#include "stringutils.h"
#include "decorators.h"


static const std::string data = "class Hello, World! __int__ = int; // \"(>.<)\" char";
static const std::string expected_code_to_html = "class Hello, World! __int__ = int; // &quot;(&gt;.&lt;)&quot; char\n";
static const std::string expected_keywords = "<font class='baseword'>class</font> Hello, World! __int__ = <font class='basetype'>int</font>; // \"(>.<)\" char\n";
static const std::string expected_lines = "<div class='line'><div class='linenum'>1</div><div class='code'>class Hello, World! __int__ = int; // \"(>.<)\" char</div></div>\n";
static const std::string expected_string = "class Hello, World! __int__ = int; // <font class='string'>&quot;(&gt;.&lt;)&quot;</font> char\n\n";
static const std::string expected_comment = "class Hello, World! __int__ = int; <font class='comment'>// \"(>.<)\" char</font>\n";
static const std::string expected_wrapping = "class Hello, World! __int__ = int; <font class='comment'>// <font class='string'>&quot;(&gt;.&lt;)&quot;</font> char</font>\n";


TEST(stringutils, find_all)
{
	const std::string data = "Hello Big big, actualy big, World!";
	const StringPositions expected = {5, 9, 14, 22, 27};

	StringPositions positions = stringutils::find_all(data, " ");

	EXPECT_EQ(expected, positions);
}


TEST(stringutils, search_replace_all)
{
	std::string data = "Hello Big big, actualy big, World!";
	const std::string expected = "Hello  Big  big,  actualy  big,  World!";

	stringutils::search_replace_all(data, " ", "  ");

	EXPECT_STREQ(expected.c_str(), data.c_str());
}


TEST(stringutils, get_insidence)
{
	const std::string data = "{{ { } { } }} {}";

	EXPECT_EQ(0, stringutils::get_insidence(data, 0, "{", "}"));
	EXPECT_EQ(1, stringutils::get_insidence(data, 1, "{", "}"));
	EXPECT_EQ(3, stringutils::get_insidence(data, 4, "{", "}"));
	EXPECT_EQ(3, stringutils::get_insidence(data, 8, "{", "}"));
	EXPECT_EQ(1, stringutils::get_insidence(data, 12, "{", "}"));

	const std::string quotes = "mystring = 'hello!'; 'simple string'";

	EXPECT_TRUE(stringutils::get_insidence(quotes, 14, "'"));
	EXPECT_FALSE(stringutils::get_insidence(quotes, 21, "'"));
	EXPECT_TRUE(stringutils::get_insidence(quotes, 27, "'"));

}


TEST(Component, StringComponent)
{
	StringComponent sc("Hello, World!");

	std::string line;
	while (!sc.is_ended())
	{
		sc >> line;
		line.insert(0, "*** ");
		line.append(" ***");
		sc << line;
	}
	sc.update();

	std::stringstream sc_ss;
	sc_ss << sc;

	EXPECT_STREQ("*** Hello, World! ***\n", sc_ss.str().c_str());
}


TEST(Component, StreamComponent)
{
	std::stringstream ss;
	ss << "*** 1st line ***" << std::endl
	   << "*** 2nd line ***" << std::endl
	   << "*** 3rd line ***" << std::endl;
	const std::string expected = ss.str();

	StreamComponent sc;
	sc << "1st line" << Component::endl
	   << "2nd line" << Component::endl
	   << "3rd line" << Component::endl;
	sc.update();

	std::string line;
	while (!sc.is_ended())
	{
		sc >> line;
		line.insert(0, "*** ");
		line.append(" ***");
		sc << line << Component::endl;
	}
	sc.update();

	std::stringstream sc_ss;
	sc_ss << sc;

	EXPECT_STREQ(expected.c_str(), sc_ss.str().c_str());
}


TEST(Decorators, CodeToHTMLDecoratorExecution)
{
	StringComponent sc(data);

	CodeToHTMLDecorator decorator;
	decorator.execute(sc);

	EXPECT_STREQ(expected_code_to_html.c_str(), sc.get_string().c_str());
}


TEST(Decorators, KeywordsHighlightDecoratorExecution)
{
	StringComponent sc(data);

	KeywordsHighlightDecorator decorator;
	decorator.execute(sc);

	EXPECT_STREQ(expected_keywords.c_str(), sc.get_string().c_str());
}


TEST(Decorators, LineNumbersDecoratorExecution)
{
	StringComponent sc(data);

	LineNumbersDecorator decorator;
	decorator.execute(sc);

	EXPECT_STREQ(expected_lines.c_str(), sc.get_string().c_str());
}


TEST(Decorators, StringHighlightDecoratorExecution)
{
	StringComponent sc(data);

	CodeToHTMLDecorator d;
	d.execute(sc);

	StringHighlightDecorator decorator;
	decorator.execute(sc);

	EXPECT_STREQ(expected_string.c_str(), sc.get_string().c_str());
}


TEST(Decorators, CommentHighlightDecoratorExecution)
{
	StringComponent sc(data);

	CommentHighlightDecorator decorator;
	decorator.execute(sc);

	EXPECT_STREQ(expected_comment.c_str(), sc.get_string().c_str());
}


TEST(Decorators, Wrapping)
{
	StringComponent sc(data);

	HTMLDecorator decorator;
	CodeToHTMLDecorator code_to_html;
	StringHighlightDecorator string_highlighter;
	CommentHighlightDecorator comment_highlighter;

	decorator
			<< code_to_html
			<< string_highlighter
			<< comment_highlighter;

	decorator.execute(sc);

	EXPECT_STREQ(expected_wrapping.c_str(), sc.get_string().c_str());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

