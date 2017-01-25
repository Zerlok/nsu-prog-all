#ifndef __COMMAND_PARSER_H__
#define __COMMAND_PARSER_H__


#include <string>
#include <vector>
#include "command.h"


class CommandParser
{
	public:
		CommandParser(CommandsBuilders& cmd_prototypes, const char& separator);
		~CommandParser();

		size_t pos_char(const std::string& data, const char& s);
		Strings split_string(const std::string& data);

		const Command::AbstractPrototype* parse(const std::string& line);

	private:
		CommandsBuilders& _cmd_prototypes;
		char _separator;
};


// __COMMAND_PARSER_H__
#endif
