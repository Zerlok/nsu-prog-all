#ifndef __SET_COMMAND_H__
#define __SET_COMMAND_H__


#include "command.h"


class SetCommand : public Command
{
	public:
		SetCommand(const std::string& value = "")
			: Command(Type::data_manipulation),
			  _value(value) {}
		SetCommand(const Strings& args)
			: Command(Type::data_manipulation),
			  _value(args[0]) {}
		~SetCommand() {}

		Result execute(const std::string&, std::string&) override
		{
			return std::move(Result(_value));
		}

	private:
		std::string _value;
};

#endif // __SET_COMMAND_H__
