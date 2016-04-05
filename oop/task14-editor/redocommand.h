#ifndef __REDO_COMMAND_H__
#define __REDO_COMMAND_H__


#include "command.h"
#include "history.h"


class RedoCommand : public Command
{
	public:
		RedoCommand()
			: Command(Type::history_manipulation) {}
		RedoCommand(const Strings&)
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


// __REDO_COMMAND_H__
#endif
