#ifndef __EDITOR_HISTORY_H__
#define __EDITOR_HISTORY_H__


#include <string>
#include <vector>


class History
{
	public:
		History();
		~History() = default;

		const std::string& get_current() const;
		void push_back(const std::string& data);

		bool has_next() const;
		bool has_previous() const;

		const std::string& next();
		const std::string& previous();

	private:
		size_t _index;
		std::vector<std::string> _data_queue;

		void _remove_after(const size_t& index);
};


// __EDITOR_HISTORY_H__
#endif
