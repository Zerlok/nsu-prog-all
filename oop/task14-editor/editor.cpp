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
	  _commands_factory(),
	  _data_history()
{
	_commands_factory.registerate<CopyCommand>("copy");
	_commands_factory.registerate<HelpCommand>("help");
	_commands_factory.registerate<InsertCommand>("insert");
	_commands_factory.registerate<RedoCommand>("redo");
	_commands_factory.registerate<SearchReplaceCommand>("sed");
	_commands_factory.registerate<SetCommand>("set");
	_commands_factory.registerate<UndoCommand>("undo");

	_data_history.push_back(_current_data);
}


Editor::~Editor()
{
}


const std::string& Editor::execute_command(Command* cmd)
{
	if (cmd == nullptr)
		return _current_data;

	Command::Result res;
	switch (cmd->get_type())
	{
		case Command::Type::data_manipulation:
			res = cmd->execute(_current_data, _buffer);
			if (res)
			{
				_current_data = res.data;
				_data_history.push_back(res.data);
			}
			break;

		case Command::Type::history_manipulation:
			res = cmd->execute(_data_history);
			if (res)
				_current_data = res.data;

			break;

		case Command::Type::help:
			((HelpCommand*)cmd)->execute(_output_stream, _commands_factory.get_registred());
			break;

		default:
		{
			std::cerr << "Unknown command type!" << std::endl;
			break;
		}
	}

	// Errors were found during command execution.
	if (!res)
		for (const Command::Error& err : res.errors)
			std::cerr << err << std::endl;

	return _current_data;
}


void Editor::run()
{
	std::string line;
	CommandParser cmd_parser(_commands_factory, ' ');

	_output_stream << ">>> ";
	_output_stream.flush();

	while (std::getline(_commands_stream, line))
	{
		Command* cmd = cmd_parser.parse(line);
		execute_command(cmd);
		delete cmd;

		_output_stream << ">>> ";
		_output_stream.flush();
	}
}
