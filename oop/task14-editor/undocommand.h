#ifndef __UNDO_COMMAND_H__
#define __UNDO_COMMAND_H__


#include "command.h"
#include "history.h"


class UndoCommand : public Command
{
	public:
		class Prototype;

		UndoCommand()
			: Command(Type::history_manipulation) {}
		~UndoCommand() {}

		Errors validate(const History& cmd_history) const override
		{
			Errors errs;

			if (!cmd_history.has_previous())
				errs.push_back(Error("No commands left for undo operation!"));

			return std::move(errs);
		}

		Result execute(History& cmd_history) override
		{
			Result res("", validate(cmd_history));

			if (!res)
				return std::move(res);

			res.data = cmd_history.previous();

			return std::move(res);
		}
};


class UndoCommand::Prototype : public AbstractPrototype
{
	public:
		Prototype()
			: AbstractPrototype() {}
		Prototype(const Strings& args)
			: AbstractPrototype(args) {}
		~Prototype() {}

		Result construct() const override
		{
			return std::move(Result(new UndoCommand()));
		}
};


// __UNDO_COMMAND_H__
#endif
