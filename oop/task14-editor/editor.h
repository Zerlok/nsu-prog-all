#ifndef __EDITOR_H__
#define __EDITOR_H__


#include <iostream>
#include <string>
#include <vector>

#include "command.h"
#include "commandparser.h"
#include "history.h"


class Editor
{
	public:
		Editor(std::istream& input, std::ostream& output);
		~Editor();

		const std::string& execute_command(Command& cmd);
		void run();

	private:
		std::string _current_data;
		std::string _buffer;
		std::istream& _commands_stream;
		std::ostream& _output_stream;
		CommandsPrototypes _commands_prototypes;
		History _data_history;

		void _yield(const std::string& s);
};


// __EDITOR_H__
#endif
