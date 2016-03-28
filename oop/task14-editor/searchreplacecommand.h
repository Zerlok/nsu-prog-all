#ifndef __SEARCH_REPLACE_COMMAND_H__
#define __SEARCH_REPLACE_COMMAND_H__


#include "command.h"


class SearchReplaceCommand : public Command
{
	public:
		SearchReplaceCommand();
		~SearchReplaceCommand();

		std::string execute(const std::string &data) override;
};


// __SEARCH_REPLACE_COMMAND_H__
#endif
