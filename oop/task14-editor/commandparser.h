#ifndef __COMMAND_PARSER_H__
#define __COMMAND_PARSER_H__


#include <string>
#include <vector>
#include "command.h"


class CommandParser
{
	public:
		CommandParser(CommandFactory& cmd_factory, const char& separator);
		~CommandParser();

		size_t pos_char(const std::string& data, const char& s);
		Strings split_string(const std::string& data);

		Command* parse(const std::string& line);

	private:
		CommandFactory& _cmd_factory;
		char _separator;
};


// __COMMAND_PARSER_H__
#endif
