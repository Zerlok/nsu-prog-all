#ifndef __HELP_COMMAND_H__
#define __HELP_COMMAND_H__


#include <iostream>
#include "command.h"


class HelpCommand : public Command
{
	public:
		class Prototype;

		HelpCommand()
			: Command(Command::Type::help) {}
		~HelpCommand() {}

		void execute(std::ostream& out, const std::vector<std::string>& cmd_names)
		{
			out << "Available commands:" << std::endl;
			for (const std::string& name : cmd_names)
				out << "  * " << name << std::endl;

			out << "  * exit" << std::endl;
		}
};


class HelpCommand::Prototype : public AbstractPrototype
{
	public:
		Prototype()
			: AbstractPrototype() {}
		Prototype(const Strings& args)
			: AbstractPrototype(args) {}
		~Prototype() {}

		Result construct() const override
		{
			return std::move(Result(new HelpCommand()));
		}
};


// __HELP_COMMAND_H__
#endif
