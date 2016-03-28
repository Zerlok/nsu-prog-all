#ifndef __UNDO_COMMAND_H__
#define __UNDO_COMMAND_H__


#include "command.h"


class UndoCommand : public Command
{
	public:
		UndoCommand();
		~UndoCommand();

		std::string execute(const std::string &data) override;
};


// __UNDO_COMMAND_H__
#endif
