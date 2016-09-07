#include <fstream>
#include <sstream>
#include <stdexcept>
#include "xprotocol.h"


bool operator==(const std::string &s1, const std::string &s2)
{
	return (!(s1.compare(s2)));
}


std::string xmodem_utils::read_all_input(const std::string &filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::stringstream ss;
		ss << "Cannot open file: " << filename;
		throw std::invalid_argument(ss.str());
	}

	std::string read_data = "";
	std::string line;

	while (std::getline(input, line))
	{
		line.append(xmodem_utils::eol_symbol);
		read_data.append(line);
	}

	return read_data;
}
