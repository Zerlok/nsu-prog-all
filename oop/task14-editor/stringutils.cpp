
#include "stringutils.h"


StringPositions stringutils::find_all(
		const std::string& data,
		const std::string& sub)
{
	StringPositions positions;
	const size_t data_len = data.size();
	const size_t sub_len = sub.size();

	if (sub_len > data_len)
		return std::move(positions);

	std::string tmp;
	size_t pos = 0;
	for (size_t offset = 0; offset < data.size(); offset = pos + sub_len)
	{
		// Skip previous data.
		tmp = data.substr(offset, data_len);
		// Find next match with substr in tmp string.
		pos = tmp.find(sub);

		// If substr not found - exit.
		if (pos == std::string::npos)
			break;

		pos += offset;
		positions.push_back(pos);
	}

	return std::move(positions);
}


int stringutils::search_replace_all(
		std::string& data,
		const std::string& sub,
		const std::string& repl)
{
	const StringPositions positions = find_all(data, sub);
	const size_t sub_len = sub.size();
	for (int i = positions.size() - 1; i >= 0; --i)
	{
		data.erase(positions[i], sub_len);
		data.insert(positions[i], repl);
	}

	return positions.size();
}


// Returns the depth of position. Depth counts on left and right strings appearence.
// If left and right string are the same, than value of depth is 1 or 0 (as with string brackets).
// Otherwise when left string appeares, depth increases, when right string appeares, depth decreases.
int stringutils::get_insidence(
		const std::string& data,
		const size_t& pos,
		const std::string& left,
		const std::string& right)
{
	int depth = 0;

	StringPositions positions = find_all(data, left);
	for (const size_t& left_pos : positions)
		if ((left_pos < pos)
				&& !((left_pos > 0) && (data[left_pos - 1] == backslash)))
			++depth;

	if (right.empty()
			|| (left.compare(right) == 0))
		return (depth % 2);

	positions = find_all(data, right);
	for (const size_t& right_pos : positions)
		if ((right_pos < pos)
				&& !((right_pos > 0) && (data[right_pos - 1] == backslash)))
			--depth;

	return depth;
}
