#include "copycommand.h"
#include "insertcommand.h"
#include "redocommand.h"
#include "searchreplacecommand.h"
#include "undocommand.h"

#include "editor.h"


size_t pos(const std::string& data, const char s)
{
	size_t p = data.find(s);
	return ((p != std::string::npos)
			? p
			: data.length());
}


std::vector<std::string> stringutils::split(
		const std::string& data,
		const char separator,
		const bool skip_empty_values = true)
{
	std::vector<std::string> strings;

	if (data.empty())
		return std::move(strings);

	std::string str = data + separator;
	const size_t max_len = str.length();
	std::string value;

	size_t separator_pos;
	while (!str.empty())
	{
		separator_pos = pos(str, separator);
		value = str.substr(0, separator_pos);

		if (!value.empty()
				|| !skip_empty_values)
			strings.push_back(value);

		str = str.substr(separator_pos+1, max_len);
	}

	return std::move(strings);
}


Editor::Editor(const std::string& data, std::istream& cmds)
	: _current_data(data),
	  _commands_stream(cmds),
	  _commands_factory(),
	  _data_history(data)
{
	_commands_factory.registerate<CopyCommand>("copy");
	_commands_factory.registerate<InsertCommand>("insert");
	_commands_factory.registerate<RedoCommand>("redo");
	_commands_factory.registerate<SearchReplaceCommand>("sed");
	_commands_factory.registerate<UndoCommand>("undo");

}


void Editor::run()
{
	std::string line;
	CommandParser cmd_parser(_commands_factory);

	while (std::getline(_commands_stream, line))
	{
		Command cmd = cmd_parser.parse(line);

		if (cmd.is_modifying())
			_data_history.push_back(_current_data);

		_current_data = cmd.execute(_current_data);
	}
}



Editor::History::History(const std::string& initial_data)
	: _index(0), _data_queue()
{
	_data_queue.push_back(initial_data);
}


const std::string& Editor::History::get_current() const
{
	return _data_queue[_index];
}


void Editor::History::push_back(const std::string& data)
{
	if (_index < _data_queue.size() - 1)
		_remove_after(_index);

	_data_queue.push_back(data);
	++_index;
}


void Editor::History::next()
{
	++_index;
}


void Editor::History::previous()
{
	--_index;
}


void Editor::History::_remove_after(const size_t& index)
{
	for (size_t i = _data_queue.size() - 1; i > index; --i)
		_data_queue.pop_back();
}
