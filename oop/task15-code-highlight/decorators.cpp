#include <sstream>
#include <string>
#include <vector>
#include "decorators.h"


size_t get_non_alpha_pos(const std::string& data)
{
	size_t i;

	for (i = 0; i < data.size(); ++i)
		if (!std::isalpha(data[i]))
			break;

	return i;
}


using Strings = std::vector<std::string>;
Strings split_to_words(const std::string& data, const char& separator)
{
	std::vector<std::string> strings;

	if (data.empty())
		return std::move(strings);

	std::string str = data + separator;
	const size_t max_len = str.length();
	std::string value;

	size_t separator_pos;
	while (!str.empty())
	{
		separator_pos = get_non_alpha_pos(str);
		value = str.substr(0, separator_pos);

		if (!value.empty())
			strings.push_back(value);

		str = str.substr(separator_pos+1, max_len);
	}

	return std::move(strings);
}


bool is_inside_string(const std::string& data, const size_t& pos)
{
	bool is_string = false;
	for (size_t i = 0; i < data.size(); ++i)
	{
		if (i == pos)
			return is_string;

		if (data[i] == '"')
			is_string = !is_string;
	}

	return is_string;
}


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
	for (size_t i = 0; i < data.size(); i = pos + sub_len)
	{
		// Skip previous data.
		tmp = data.substr(i, data_len);
		// Find next match with substr.
		pos = tmp.find(substr);

		// If substr not found - exit.
		if (pos == std::string::npos)
			break;

		pos += i;
		// If substr found - check for exact match and save position of substr.
		if (((pos == 0) || (!std::isalpha(data[pos - 1])))
				&& ((pos + sub_len == data_len) || (!std::isalpha(data[pos + sub_len])))
				&& (!is_inside_string(data, pos)))
			posis.push_back(pos);
	}

	return std::move(posis);
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
//		search_replace(line, "\"", "&quot;");
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
	"bool",
	"break",
	"case",
	"catch",
	"char",
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
	"static",
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


bool KeywordsHighlightDecorator::highlight(
		std::string& data,
		const std::string& word,
		const std::string& left_tag,
		const std::string& right_tag)
{
	const size_t tags_len = left_tag.size() + right_tag.size();
	const size_t word_size = word.size();
	StringPositions positions = find_all(data, word);

	for (size_t i = 0; i < positions.size(); ++i)
	{
		if (!right_tag.empty())
			data.insert(positions[i] + i*tags_len + word_size, right_tag);

		data.insert(positions[i] + i*tags_len, left_tag);
	}

	return (!positions.empty());
}


void KeywordsHighlightDecorator::execute(std::istream& in, std::ostream& out)
{
	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		if (highlight(line, "//", "<font class='comment'>"))
		{
			ss << line << "</font>" << std::endl;
			continue;
		}

//		highlight(line, "class", "<font class='baseword'>", "</font>");

		for (const std::string& word : _macroses)
			highlight(line, word, "<font class='macros'>", "</font>");

		for (const std::string& word : _basewords)
			highlight(line, word, "<font class='baseword'>", "</font>");

		for (const std::string& word : _basetypes)
			highlight(line, word, "<font class='basetype'>", "</font>");

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
