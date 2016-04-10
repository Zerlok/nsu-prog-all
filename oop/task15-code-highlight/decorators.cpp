#include <string>
#include <vector>
#include "decorators.h"


size_t get_non_alpha_pos(const std::string& data, const char& s)
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
		separator_pos = get_non_alpha_pos(str, separator);
		value = str.substr(0, separator_pos);

		if (!value.empty())
			strings.push_back(value);

		str = str.substr(separator_pos+1, max_len);
	}

	return std::move(strings);
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
				&& ((pos + sub_len == data_len) || (!std::isalpha(data[pos + sub_len]))))
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
		_inner->execute(in, out);
}


void HTMLDecorator::execute(std::istream& in, std::ostream& out)
{
	out << "<html><body>" << std::endl;
	Decorator::execute(in, out);
	out << "</body></html>";
}


void LineNumbersDecorator::execute(std::istream& in, std::ostream& out)
{
	std::string line;
	size_t num = 1;

	while (getline(in, line))
	{
		out << num << " | ";
		Decorator::execute(in, out);
		out << std::endl;
		++num;
	}
}


const KeywordsHighlightDecorator::WordsSet KeywordsHighlightDecorator::_basetypes = {
	"void",
	"int",
	"char",
	"const",
	"static"
};
const KeywordsHighlightDecorator::WordsSet KeywordsHighlightDecorator::_basewords = {
	"public",
	"protected",
	"private",
	"inline",
	"override",
	"return",
	"for",
	"while",
	"if",
	"else",
	"nullptr",
	"new",
	"delete"
};


void KeywordsHighlightDecorator::execute(std::istream& in, std::ostream& out)
{
	static const std::string bold_begin = "<b>";
	static const std::string bold_end = "</b>";
	static const size_t bold_begin_len = bold_begin.size();
	static const size_t bold_end_len = bold_end.size();

	std::string line;
	StringPositions posis;

	while (getline(in, line))
	{
		for (const std::string& word : _basetypes)
		{
			const size_t word_size = word.size();
			posis = find_all(line, word);

			for (size_t i = 0; i < posis.size(); ++i)
			{
				line.insert(posis[i] + i*(bold_begin_len + bold_end_len) + word_size, bold_end);
				line.insert(posis[i] + i*(bold_begin_len + bold_end_len), bold_begin);
			}
		}

		out << line << std::endl;
	}
}
