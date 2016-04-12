#include "stringutils.h"
#include "decorators.h"


Component::Component()
	: _text_stream()
{
}


Component::Component(std::istream &in)
	: _text_stream()
{
	std::string line;
	while (std::getline(in, line))
		_text_stream << line << std::endl;
}


std::string Component::get_line()
{
	std::string line;
	_input_pos = _text_stream.tellp();
//	_output_pos = _text_stream;
	std::getline(_text_stream, line);

	return std::move(line);
}

/*
ostringstream& insert( ostringstream& oss, const string& s )
{
streamsize pos = oss.tellp();
oss.str( s + oss.str() );
oss.seekp( pos + s.length() );
return oss;
}
*/

void Component::reset_line(const std::string& line)
{
	_text_stream.seekg(_input_pos);
	_text_stream << line << std::endl;
}


std::istream& operator>>(std::istream& in, Component& component)
{
	std::string line;
	while (std::getline(in, line))
		component._text_stream << line << std::endl;

	return in;
}


std::ostream& operator<<(std::ostream& out, Component& component)
{
	std::string line;
	while (std::getline(component._text_stream, line))
		out << line << std::endl;

	return out;
}


Decorator::~Decorator()
{
	delete _inner;
}


void Decorator::wrap(Decorator& inner)
{
	// none.
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
		stringutils::search_replace_all(line, "<", "&lt;");
		stringutils::search_replace_all(line, ">", "&gt;");
		stringutils::search_replace_all(line, "\"", "&quot;");
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
	"class",
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
	const size_t word_len = word.size();
	StringPositions positions = stringutils::find_all(data, word);

	for (int i = positions.size() - 1; i >= 0; --i)
	{
		const size_t& pos = positions[i];
		const size_t& data_len = data.size();
		// Check keyword is located in usual code space,
		// skip it if keyword is inside string or comment or subword.
		if (stringutils::get_insidence(data, pos, "&quot;")		// skip string
				|| stringutils::get_insidence(data, pos, "//")	// skip comment
				|| (stringutils::get_insidence(data, pos, "<", ">") // skip html attributes
					&& (pos + word_len < data_len)
					&& (data[pos + word_len] == '='))
				|| ((pos > 0)
					&& (std::isalnum(data[pos - 1])
						|| (data[pos - 1] == '_')))
				|| ((pos + word_len < data.size())
					&& (std::isalnum(data[pos + word_len])
						|| (data[pos + word_len] == '_'))))
			continue;

		if (!right_tag.empty())
			data.insert(positions[i] + word_len, right_tag);

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
	static const size_t left_tag_len = left_tag.size();
	static const size_t tags_len = left_tag_len + right_tag.size();
	static const std::string quot = "&quot;";
	static const size_t quout_size = quot.size();

	std::string line;
	std::stringstream ss;
	StringPositions positions;
	size_t quot_num;
	size_t insert_pos;
	size_t checking_pos;
	const std::string* tag;

	while (std::getline(in, line))
	{
		quot_num = 0;
		positions = stringutils::find_all(line, quot);

		for (size_t i = 0; i < positions.size(); ++i)
		{
			// For quot begin.
			if (quot_num % 2 == 0)
			{
				insert_pos = positions[i] + (quot_num / 2) * tags_len;
				checking_pos = insert_pos - 1;
				tag = &left_tag;
			}

			// For quot end.
			else
			{
				checking_pos = positions[i] + ((quot_num - 1) / 2) * tags_len + left_tag_len - 1;
				insert_pos = checking_pos + 1 + quout_size;
				tag = &right_tag;
			}

			if ((checking_pos < line.size())
					&& (line[checking_pos] == stringutils::backslash))
				continue;

			line.insert(insert_pos, *tag);
			++quot_num;
		}

		ss << line << std::endl;
	}

	Decorator::execute(ss, out);
}
