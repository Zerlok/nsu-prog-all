#ifndef __COMMAND_PARSER_H__
#define __COMMAND_PARSER_H__


#include "command.h"


class CommandParser
{
	public:
		CommandParser(CommandFactory& cmd_factory);
		~CommandParser();

	private:
		CommandFactory& _cmd_factory;
};


// __COMMAND_PARSER_H__
#endif
