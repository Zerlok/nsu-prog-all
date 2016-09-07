#ifndef __REDO_COMMAND_H__
#define __REDO_COMMAND_H__


#include "command.h"


class RedoCommand : public Command
{
	public:
		RedoCommand();
		~RedoCommand();

		std::string execute(const std::string &data) override;
};


// __REDO_COMMAND_H__
#endif
