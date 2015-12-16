#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include <string>
#include <iostream>


namespace xmodem_protocol
{
	static const std::string successed_transmission_cmd = "<OK>";
	static const std::string failed_transmitting_cmd = "<NOK>";

	static const int max_tries = 8;

	static const std::string data_end = "<EOF>";
}

namespace xmodem_utils
{
	static const std::string eol_symbol = "\n";

	bool operator==(const std::string &s1, const std::string &s2);
	std::string read_all_input(const std::string &filename);
}


// __PROTOCOL_H__
#endif
