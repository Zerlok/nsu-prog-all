#ifndef __SET_COMMAND_H__
#define __SET_COMMAND_H__


#include <sstream>
#include "command.h"


class SetCommand : public Command
{
	public:
		class Prototype;

		SetCommand(const std::string& value)
			: Command(Type::data_manipulation),
			  _value(value) {}
		~SetCommand() {}

		Result execute(const std::string&, std::string&) override
		{
			return std::move(Result(_value));
		}

	private:
		std::string _value;
};


class SetCommand::Prototype : public AbstractPrototype
{
	public:
		Prototype()
			: AbstractPrototype() {}
		Prototype(const Strings &args)
			: AbstractPrototype(args) {}
		~Prototype() {}

		Result construct() const override
		{
			Result res;

			if (!arguments.empty())
			{
				std::stringstream ss;
				for (size_t i = 0; i < arguments.size() - 1; ++i)
					ss << arguments[i] << ' ';

				ss << arguments.back();
				res.ptr = new SetCommand(ss.str());
			}
			else
				res.errors.push_back(Error(Error::type::invalid_arguments_num, "One argument is required: a new string."));

			return std::move(res);
		}
};


// __SET_COMMAND_H__
#endif
