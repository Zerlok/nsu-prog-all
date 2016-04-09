#include "copycommand.h"
#include "helpcommand.h"
#include "insertcommand.h"
#include "redocommand.h"
#include "searchreplacecommand.h"
#include "setcommand.h"
#include "undocommand.h"

#include "editor.h"


Editor::Editor(std::istream& input, std::ostream& output)
	: _current_data(),
	  _buffer(),
	  _commands_stream(input),
	  _output_stream(output),
	  _commands_prototypes(),
	  _data_history()
{
	_commands_stream >> std::noskipws;

	_commands_prototypes.registerate<CopyCommand>("copy");
	_commands_prototypes.registerate<HelpCommand>("help");
	_commands_prototypes.registerate<InsertCommand>("insert");
	_commands_prototypes.registerate<RedoCommand>("redo");
	_commands_prototypes.registerate<SearchReplaceCommand>("sed");
	_commands_prototypes.registerate<SetCommand>("set");
	_commands_prototypes.registerate<UndoCommand>("undo");

	_data_history.push_back(_current_data);
}


Editor::~Editor()
{
	_commands_stream >> std::skipws;
}


const std::string& Editor::execute_command(Command& cmd)
{
	Command::Result res;
	switch (cmd.get_type())
	{
		case Command::Type::data_manipulation:
			res = cmd.execute(_current_data, _buffer);
			if (res)
			{
				_current_data = res.data;
				_data_history.push_back(res.data);
			}
			break;

		case Command::Type::history_manipulation:
			res = cmd.execute(_data_history);
			if (res)
				_current_data = res.data;

			break;

		case Command::Type::help:
			((HelpCommand&)cmd).execute(_output_stream, _commands_prototypes.get_registred());
			break;
	}

	// Errors were found during command execution.
	if (!res)
		for (const Error& e : res.errors)
			_output_stream << e << std::endl;

	return _current_data;
}


void Editor::run()
{
	bool is_exit = false;
	std::string line;
	CommandParser cmd_parser(_commands_prototypes, ' ');

	while (!is_exit)
	{
		_yield("IN: ");
		std::getline(_commands_stream, line);

		// Special word for exiting.
		if (line.compare("exit") == 0)
		{
			is_exit = true;
			break;
		}

		const Command::AbstractPrototype* cmd_prototype = cmd_parser.parse(line);
		// If command prototype were not found.
		if (cmd_prototype == nullptr)
		{
			_output_stream << Error("Invalid command name!", line) << std::endl;
			continue;
		}

		Command::AbstractPrototype::Result res = cmd_prototype->construct();
		// If errors were found during construction.
		if (!res)
		{
			for (const Error& e : res.errors)
				_output_stream << e << std::endl;
			continue;
		}

		// Execute the constructed command.
		_output_stream << "OUT: " << execute_command(*(res.ptr)) << std::endl;
	}
}


void Editor::_yield(const std::string& s)
{
	_output_stream << s;
	_output_stream.flush();
}
