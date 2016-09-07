#ifndef __COPY_COMMAND_H__
#define __COPY_COMMAND_H__


#include "command.h"


class CopyCommand : public Command
{
	public:
		CopyCommand();
		~CopyCommand();

		std::string execute(const std::string &data) override;
};


// __COPY_COMMAND_H__
#endif
