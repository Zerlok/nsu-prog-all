#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__


#include <string>
#include <vector>


using StringPositions = std::vector<size_t>;


namespace stringutils
{
	static const char backslash = '\\';

	StringPositions find_all(const std::string& data, const std::string& substr);
	int search_replace_all(std::string& data, const std::string& sub, const std::string& repl);
	int get_insidence(const std::string& data, const size_t& pos, const std::string& left, const std::string& right = "");
}


// __STRING_UTILS_H__
#endif
