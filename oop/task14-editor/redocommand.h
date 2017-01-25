#ifndef __REDO_COMMAND_H__
#define __REDO_COMMAND_H__


#include "command.h"
#include "history.h"


class RedoCommand : public Command
{
	public:
		class Prototype;

		RedoCommand()
			: Command(Type::history_manipulation) {}
		~RedoCommand() {}

		Errors validate(const History& cmd_history) const override
		{
			Errors errs;

			if (!cmd_history.has_next())
				errs.push_back(Error("No commands left for redo operation!"));

			return std::move(errs);
		}

		Result execute(History& cmd_history) override
		{
			Result res("", validate(cmd_history));

			if (!res)
				return std::move(res);

			res.data = cmd_history.next();

			return std::move(res);
		}
};


class RedoCommand::Prototype : public AbstractPrototype
{
	public:
		Prototype()
			: AbstractPrototype() {}
		Prototype(const Strings& args)
			: AbstractPrototype(args) {}
		~Prototype() {}

		Result construct() const override
		{
			return std::move(Result(new RedoCommand()));
		}
};


// __REDO_COMMAND_H__
#endif
