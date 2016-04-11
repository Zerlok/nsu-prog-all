#include <sstream>
#include <string>
#include <vector>
#include "decorators.h"


using StringPositions = std::vector<size_t>;
StringPositions find_all(const std::string& data, const std::string& substr)
{
	StringPositions posis;
	const size_t data_len = data.size();
	const size_t sub_len = substr.size();

	if (sub_len > data_len)
		return std::move(posis);

	std::string tmp;
	size_t pos = 0;
	for (size_t offset = 0; offset < data.size(); offset = pos + sub_len)
	{
		// Skip previous data.
		tmp = data.substr(offset, data_len);
		// Find next match with substr in tmp string.
		pos = tmp.find(substr);

		// If substr not found - exit.
		if (pos == std::string::npos)
			break;

		pos += offset;
		posis.push_back(pos);
	}

	return std::move(posis);
}


// Returns the depth of position. Depth counts on left and right strings appearence.
// If left and right string are the same, than value of depth is 1 or 0 (as with string brackets).
// Otherwise when left string appeares, depth increases, when right string appeares, depth decreases.
int get_insidence(const std::string& data, const size_t& pos, const std::string& left, std::string right = "")
{
	if (right.empty())
		right = left;

	StringPositions positions = find_all(data, left);
	int depth = 0;
	for (const size_t& left_pos : positions)
		if ((left_pos < pos)
				&& !((left_pos > 0) && (data[left_pos - 1] == '\\')))
			++depth;

	if (left.compare(right) == 0)
		return (depth % 2);

	positions = find_all(data, right);
	for (const size_t& right_pos : positions)
		if ((right_pos < pos)
				&& !((right_pos > 0) && (data[right_pos - 1] == '\\')))
			--depth;

	return depth;
}


Decorator::~Decorator()
{
	delete _inner;
}


void Decorator::execute(std::istream& in, std::ostream& out)
{
	if (_inner != nullptr)
	{
		_inner->execute(in, out);
		return;
	}

	std::string line;
	while (std::getline(in, line))
		out << line << std::endl;
}


void HTMLDecorator::search_replace(std::string& data, const std::string& sub, const std::string& repl)
{
	const size_t sub_len = sub.size();

	size_t pos = data.find(sub);
	while (pos != std::string::npos)
	{
		data.erase(pos, sub_len);
		data.insert(pos, repl);
		pos = data.find(sub);
	}
}


void HTMLDecorator::execute(std::istream& in, std::ostream& out)
{
	std::string line;
	std::stringstream ss;

	// TODO: load from css file.
	out << "<!DOCTYPE html>" << std::endl
		<< "<html>" << std::endl
		<< "<head>" << std::endl
		<< "<style>" << std::endl
		<< "pre {-moz-tab-size: 4; tab-size: 4;}" << std::endl
		<< "div, font {font-family: Ubuntu Mono, Monospace; }" << std::endl
		<< "div {display: inline-block; }" << std::endl
		<< "div.line {width: 100%; }" << std::endl
		<< "div.line:hover {background: #EAEAEA; }" << std::endl
		<< "div.linenum {text-align: right; width: 35px; color: #808080; margin-right: 10px; }" << std::endl
		<< "font.macros, font.basetype, font.baseword {font-weight: bold; }" << std::endl
		<< "font.macros {color: #909090; }" << std::endl
		<< "font.basetype {font-style: italic; }" << std::endl
		<< "font.comment {color: #A0A0A0; font-style: italic; }" << std::endl
		<< "font.string {color: #A0A050; }" << std::endl
		<< "</style>" << std::endl;

	out << "<body>" << std::endl
		<< "<pre>" << std::endl;

	while (std::getline(in, line))
	{
		search_replace(line, "<", "&lt;");
		search_replace(line, ">", "&gt;");
		search_replace(line, "\"", "&quot;");
		ss << line << std::endl;
	}

	Decorator::execute(ss, out);
	out << "</pre>" << std::endl
		<< "</body>" << std::endl
		<< "</html>" << std::endl;
}


void LineNumbersDecorator::execute(std::istream& in, std::ostream& out)
{
	size_t num = 1;
	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		ss << "<div class='line'><div class='linenum'>" << num << "</div>"
		   << "<div class='code'>" << line << "</div></div>"
		   << std::endl;
		++num;
	}

	Decorator::execute(ss, out);
}


const KeywordsHighlightDecorator::WordsSet KeywordsHighlightDecorator::_macroses = {
	"#if",
	"#elif",
	"#else",
	"#endif",
	"#defined",
	"#ifdef",
	"#ifndef",
	"#define",
	"#undef",
	"#include",
	"#line",
	"#error",
	"#pragma"
};
const KeywordsHighlightDecorator::WordsSet KeywordsHighlightDecorator::_basetypes = {
	"void",
	"bool",
	"int",
	"char",
	"char16_t",
	"char32_t",
	"short",
	"long",
	"float",
	"double",
	"signed",
	"unsigned",
	"const",
	"static"
};
const KeywordsHighlightDecorator::WordsSet KeywordsHighlightDecorator::_basewords = {
	"alignas",
	"alignof",
	"and",
	"and_eq",
	"asm",
	"auto",
	"bitand",
	"bitor",
	"break",
	"case",
	"catch",
//	"class",
	"compl",
	"concept",
	"constexpr",
	"const_cast",
	"continue",
	"decltype",
	"default",
	"delete",
	"do",
	"dynamic_cast",
	"else",
	"enum",
	"explicit",
	"export",
	"extern",
	"false",
	"for",
	"friend",
	"goto",
	"if",
	"inline",
	"mutable",
	"namespace",
	"new",
	"noexcept",
	"not",
	"not_eq",
	"nullptr",
	"operator",
	"or",
	"or_eq",
	"private",
	"protected",
	"public",
	"register",
	"reinterpret_cast",
	"requires",
	"return",
	"sizeof",
	"static_assert",
	"static_cast",
	"struct",
	"switch",
	"template",
	"this",
	"thread_local",
	"throw",
	"true",
	"try",
	"typedef",
	"typeid",
	"typename",
	"union",
	"using",
	"virtual",
	"volatile",
	"wchar_t",
	"while",
	"xor",
	"xor_eq",
};


size_t KeywordsHighlightDecorator::highlight(
		std::string& data,
		const std::string& word,
		const std::string& left_tag,
		const std::string& right_tag)
{
	size_t highlights_num = 0;
	const size_t word_size = word.size();
	StringPositions positions = find_all(data, word);

	for (int i = positions.size() - 1; i >= 0; --i)
	{
		const size_t& pos = positions[i];
		// Check keyword is located in usual code space,
		// skip it if keyword is inside string or comment or subword.
		if (get_insidence(data, pos, "&quot;")				// skip string
				|| get_insidence(data, pos, "//")			// skip comment
				|| ((pos > 0)
					&& (std::isalnum(data[pos - 1])
						|| (data[pos - 1] == '_')))
				|| ((pos + word_size < data.size())
					&& (std::isalnum(data[pos + word_size])
						|| (data[pos + word_size] == '_'))))
			continue;

		if (!right_tag.empty())
			data.insert(positions[i] + word_size, right_tag);

		data.insert(positions[i], left_tag);
		++highlights_num;
	}

	return highlights_num;
}


void KeywordsHighlightDecorator::execute(std::istream& in, std::ostream& out)
{
	static const std::string macros_tag = "<font class='macros'>";
	static const std::string baseword_tag = "<font class='baseword'>";
	static const std::string basetype_tag = "<font class='basetype'>";
	static const std::string comment_tag = "<font class='comment'>";
	static const std::string close_tag = "</font>";

	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		highlight(line, "class", baseword_tag, close_tag);

		for (const std::string& word : _macroses)
			highlight(line, word, macros_tag, close_tag);

		for (const std::string& word : _basewords)
			highlight(line, word, baseword_tag, close_tag);

		for (const std::string& word : _basetypes)
			highlight(line, word, basetype_tag, close_tag);

		// TODO: Create CommentHighlitDecorator.
		if (highlight(line, "//", comment_tag))
		{
			ss << line << close_tag << std::endl;
			continue;
		}

		ss << line << std::endl;
	}

	Decorator::execute(ss, out);
}


void StringHighlightDecorator::execute(std::istream& in, std::ostream& out)
{
	static const std::string left_tag = "<font class='string'>";
	static const std::string right_tag = "</font>";
	static const size_t left_tag_size = left_tag.size();
	static const size_t tags_len = left_tag_size + right_tag.size();

	std::string line;
	std::stringstream ss;
	StringPositions positions;

	while (std::getline(in, line))
	{
		positions = find_all(line, "\"");

		for (size_t i = 0; i < positions.size(); ++i)
		{
			if ((i % 2) == 0)
				line.insert(positions[i] + i*tags_len, left_tag);
			else
				line.insert(positions[i] + 1 + left_tag_size + i*tags_len, right_tag);
		}

		ss << line << std::endl;
	}

	Decorator::execute(ss, out);
}
