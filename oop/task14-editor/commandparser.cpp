#include "commandparser.h"


size_t CommandParser::pos_char(const std::string& data, const char& s)
{
	size_t p = data.find(s);
	return ((p != std::string::npos)
			? p
			: data.length());
}


Strings CommandParser::split_string(const std::string& data)
{
	std::vector<std::string> strings;

	if (data.empty())
		return std::move(strings);

	std::string str = data + _separator;
	const size_t max_len = str.length();
	std::string value;

	size_t separator_pos;
	while (!str.empty())
	{
		separator_pos = pos_char(str, _separator);
		value = str.substr(0, separator_pos);

		if (!value.empty())
			strings.push_back(value);

		str = str.substr(separator_pos+1, max_len);
	}

	return std::move(strings);
}


CommandParser::CommandParser(CommandFactory& cmd_factory, const char& separator)
	: _cmd_factory(cmd_factory),
	  _separator(separator)
{
}


CommandParser::~CommandParser()
{
}


Command* CommandParser::parse(const std::string& line)
{
	Strings args = split_string(line);
	const std::string cmd_name = args[0];
	args.erase(args.begin());

	return _cmd_factory.create(cmd_name, args);
}

