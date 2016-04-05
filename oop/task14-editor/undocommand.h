#ifndef __UNDO_COMMAND_H__
#define __UNDO_COMMAND_H__


#include "command.h"
#include "history.h"


class UndoCommand : public Command
{
	public:
		UndoCommand()
			: Command(Type::history_manipulation) {}
		UndoCommand(const Strings&)
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


// __UNDO_COMMAND_H__
#endif
