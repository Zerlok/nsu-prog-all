#ifndef __INSERT_COMMAND_H__
#define __INSERT_COMMAND_H__


#include "command.h"


class InsertCommand : public Command
{
	public:
		InsertCommand();
		~InsertCommand();

		std::string execute(const std::string &data) override;
};


// __INSERT_COMMAND_H__
#endif
