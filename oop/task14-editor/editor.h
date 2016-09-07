#ifndef __EDITOR_H__
#define __EDITOR_H__


#include <iostream>
#include <string>
#include <vector>

#include "command.h"
#include "commandparser.h"


class Editor
{
	public:
		class History;

		Editor(const std::string& data, std::istream& cmds);
		~Editor();

		void execute_command(const Command& cmd);
		void run();

	private:
		std::string _current_data;
		std::istream& _commands_stream;
		CommandFactory _commands_factory;
		History _data_history;
};


class Editor::History
{
	public:
		History(const std::string& initial_data);
		~History() = default;

		const std::string& get_current() const;
		void push_back(const std::string& data);

		void next();
		void previous();

	private:
		size_t _index;
		std::vector<const std::string> _data_queue;

		void _remove_after(const size_t& index);
};

#endif // __EDITOR_H__
