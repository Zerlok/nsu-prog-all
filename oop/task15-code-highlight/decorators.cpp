#include "stringutils.h"
#include "decorators.h"


HTMLComponent::HTMLComponent(std::istream& in)
	: StreamComponent(in)
{
}


void HTMLComponent::add_style(const std::string& style)
{
	_styles << style << std::endl;
}


std::ostream& operator<<(std::ostream& out, const HTMLComponent& component)
{
	out << htmltags::doctype << std::endl
		<< htmltags::b_html << std::endl;

	// Add CSS styles to header.
	const std::string styles = component._styles.str();
	if (!styles.empty())
		out << htmltags::b_head << std::endl
			<< htmltags::b_style << std::endl
			<< styles << std::endl
			<< htmltags::e_style << std::endl
			<< htmltags::e_head << std::endl;

	// Add component data.
	std::string line;
	out << htmltags::b_body << std::endl
		<< htmltags::b_code << std::endl
		<< ((StreamComponent&)component)
		<< htmltags::e_code << std::endl
		<< htmltags::e_body << std::endl
		<< htmltags::e_html << std::endl;

	return out;
}


HTMLDecorator& HTMLDecorator::operator<<(HTMLDecorator& inner)
{
	wrap(inner);
	return inner;
}


void CodeToHTMLDecorator::execute(std::string& line)
{
	stringutils::search_replace_all(line, symbols::code::lt, symbols::html::lt);
	stringutils::search_replace_all(line, symbols::code::gt, symbols::html::gt);
	stringutils::search_replace_all(line, symbols::code::quot, symbols::html::quot);
	HTMLDecorator::execute(line);
}


void CodeToHTMLDecorator::execute(Component& component)
{
	std::string line;
	while (!component.is_ended())
	{
		component >> line;
		execute(line);
		component << line << Component::endl;
	}

	component.update();
}


const size_t&LineNumbersDecorator::get_line_num() const
{
	return _line_num;
}


void LineNumbersDecorator::reset_line_num()
{
	_line_num = 1;
}


void LineNumbersDecorator::add_style(HTMLComponent& component)
{
	component.add_style("\
div.line, div.linenum, div.code { display: inline-block; } \
div.line { width: 100%; } \
div.line:hover { background: #EAEAEA; } \
div.linenum { text-align: right; width: 35px; color: #808080; margin-right: 10px; }");
	HTMLDecorator::add_style(component);
}


void LineNumbersDecorator::execute(Component& component)
{
	static const std::string div_line = "<div class='line'>";
	static const std::string div_num = "<div class='linenum'>";
	static const std::string div_code = "<div class='code'>";
	static const std::string close_tag = "</div>";

	std::string line;
	while (!component.is_ended())
	{
		component >> line;
		HTMLDecorator::execute(line);
		component << div_line
				  << div_num << _line_num << close_tag
				  << div_code << line << close_tag
				  << close_tag
				  << Component::endl;
		++_line_num;
	}

	reset_line_num();
	component.update();
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

		if (stringutils::get_insidence(data, pos, symbols::html::quot)							// skip string
				|| stringutils::get_insidence(data, pos, symbols::code::comment)				// skip comment
				|| (stringutils::get_insidence(data, pos, symbols::code::lt, symbols::code::gt) // skip html attribute
					&& (pos + word_len < data_len)
					&& (data[pos + word_len] == '='))
				// Check that it is a clear keyword (not a subword).
				|| ((pos > 0)
					&& (std::isalnum(data[pos - 1])
						|| (data[pos - 1] == '_')))
				|| ((pos + word_len < data.size())
					&& (std::isalnum(data[pos + word_len])
						|| (data[pos + word_len] == '_'))))
			continue;

		// Insert right tag firstly.
		if (!right_tag.empty())
			data.insert(positions[i] + word_len, right_tag);

		// Insert the left tag.
		data.insert(positions[i], left_tag);
		++highlights_num;
	}

	return highlights_num;
}


void KeywordsHighlightDecorator::add_style(HTMLComponent& component)
{
	component.add_style("\
font.macros, font.basetype, font.baseword { font-weight: bold; } \
font.macros { color: #909090; } \
font.basetype { font-style: italic; }");
	HTMLDecorator::add_style(component);
}


void KeywordsHighlightDecorator::execute(std::string& line)
{
	static const std::string macros_tag = "<font class='macros'>";
	static const std::string baseword_tag = "<font class='baseword'>";
	static const std::string basetype_tag = "<font class='basetype'>";
	static const std::string close_tag = "</font>";

	for (const std::string& word : _macroses)
		highlight(line, word, macros_tag, close_tag);

	for (const std::string& word : _basewords)
		highlight(line, word, baseword_tag, close_tag);

	for (const std::string& word : _basetypes)
		highlight(line, word, basetype_tag, close_tag);

	HTMLDecorator::execute(line);
}


void KeywordsHighlightDecorator::execute(Component& component)
{
	std::string line;
	while (!component.is_ended())
	{
		component >> line;
		execute(line);
		component << line << Component::endl;
	}

	component.update();
}


void StringHighlightDecorator::add_style(HTMLComponent& component)
{
	component.add_style("font.string {color: #858540; }");
	HTMLDecorator::add_style(component);
}


void StringHighlightDecorator::execute(std::string& line)
{
	static const std::string left_tag = "<font class='string'>";
	static const std::string right_tag = "</font>";
	static const size_t left_tag_len = left_tag.size();
	static const size_t tags_len = left_tag_len + right_tag.size();
	static const std::string& quot = symbols::html::quot;
	static const size_t quout_size = quot.size();

	size_t quot_num = 0;
	size_t insert_pos;
	size_t checking_pos;
	const std::string* tag;
	StringPositions positions = stringutils::find_all(line, quot);

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

		// Check for clear quot (without backslash symbol at left).
		if ((checking_pos < line.size())
				&& (line[checking_pos] == stringutils::backslash))
			continue;

		line.insert(insert_pos, *tag);
		++quot_num;
	}

	HTMLDecorator::execute(line);
}


void StringHighlightDecorator::execute(Component& component)
{
	std::string line;
	while (!component.is_ended())
	{
		component >> line;
		execute(line);
		component << line << Component::endl;
	}

	component.update();
}


void CommentHighlightDecorator::add_style(HTMLComponent& component)
{
	component.add_style("font.comment { color: #A0A0A0; font-style: italic; }");
	HTMLDecorator::add_style(component);
}


void CommentHighlightDecorator::execute(std::string& line)
{
	static const std::string comment_tag = "<font class='comment'>";
	static const std::string close_tag = "</font>";

	StringPositions positions = stringutils::find_all(line, symbols::code::comment);
	for (const size_t& pos : positions)
	{
		if ((pos == 0)
				|| ((line[pos - 1] != stringutils::backslash)
					&& (!stringutils::get_insidence(line, pos, symbols::html::quot))))
		{
			line.insert(pos, comment_tag);
			line.append(close_tag);
			break;
		}
	}

	HTMLDecorator::execute(line);
}


void CommentHighlightDecorator::execute(Component& component)
{
	std::string line;
	while (!component.is_ended())
	{
		component >> line;
		execute(line);
		component << line << Component::endl;
	}

	component.update();
}
