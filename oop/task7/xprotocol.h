#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include <string>


namespace xmodem_protocol
{
	static const std::string successed_transmission_cmd = "<OK>";
	static const std::string failed_transmitting_cmd = "<NOK>";

	static const int max_fails_in_row_num = 8;
}


// __PROTOCOL_H__
#endif
