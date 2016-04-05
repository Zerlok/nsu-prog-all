#ifndef __HELP_COMMAND_H__
#define __HELP_COMMAND_H__


#include <iostream>
#include "command.h"


class HelpCommand : public Command
{
	public:
		HelpCommand()
			: Command(Command::Type::help) {}
		HelpCommand(const Strings&)
			: Command(Command::Type::help) {}
		~HelpCommand() {}

		void execute(std::ostream& out, const std::vector<std::string>& cmd_names)
		{
			out << "Help message: Available commands:" << std::endl;
			for (const std::string& name : cmd_names)
				out << "  * " << name << std::endl;
		}
};


// __HELP_COMMAND_H__
#endif
