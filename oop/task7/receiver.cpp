#include <sstream>
#include "receiver.h"


const DataPackage Receiver::success_cmd_pckg = DataPackage(xmodem_protocol::successed_transmission_cmd);
const DataPackage Receiver::fail_cmd_pckg = DataPackage(xmodem_protocol::failed_transmitting_cmd);


Receiver::Receiver()
	: _packages(),
	  _fails_in_row_counter(0),
	  _total_packages_num(0),
	  _outgoing_cmd(fail_cmd_pckg),
	  _status(Status::disconnected)
{
}


Receiver::~Receiver()
{
}


const Receiver::Status &Receiver::get_status() const
{
	return _status;
}


bool Receiver::is_stopped() const
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return true;

		case Status::package_receiving_succeessful:
		case Status::package_receiving_failed:
		case Status::outgoing_command_sending_failed:
		default:
			return false;
	}
}


const DataPackage &Receiver::give_outgoing_package()
{
	switch (_status)
	{
		case Status::data_transmission_finished:
		case Status::package_receiving_succeessful:
			_outgoing_cmd = success_cmd_pckg;
			break;

		case Status::disconnected:
		case Status::package_receiving_failed:
		case Status::connection_lost:
			_outgoing_cmd = fail_cmd_pckg;
			break;

		case Status::outgoing_command_sending_failed:
		default:
			break;
	}

	return _outgoing_cmd;
}


void Receiver::take_incoming_package(const DataPackage &package)
{
	if (!package.is_valid())
	{
		++_fails_in_row_counter;
		_status = ((_fails_in_row_counter < xmodem_protocol::max_fails_in_row_num)
				   ? Status::package_receiving_failed
				   : Status::connection_lost);
		return;
	}

	const std::string &income_data = package.get_data();
	size_t fail_cmd_pos = income_data.find(xmodem_protocol::failed_transmitting_cmd);

	if (fail_cmd_pos != std::string::npos)
	{
		++_fails_in_row_counter;
		_status = ((_fails_in_row_counter < xmodem_protocol::max_fails_in_row_num)
				   ? Status::outgoing_command_sending_failed
				   : Status::connection_lost);
	}
	else // Save received data block.
	{
		if (_total_packages_num > 0)
			_packages.push_back(package);
		else // Set total packages num.
			_total_packages_num = std::stoi(package.get_data());

		_fails_in_row_counter = 0;
		_status	= ((int(_packages.size()) < _total_packages_num)
				   ? Status::package_receiving_succeessful
				   : Status::data_transmission_finished);
	}
}


std::string Receiver::get_data() const
{
	if (_total_packages_num != get_received_packages_num())
		return "";

	std::stringstream ss;
	for (const DataPackage &package : _packages)
		ss << package.get_data();

	return ss.str();
}


int Receiver::get_received_packages_num() const
{
	return _packages.size();
}


int Receiver::get_total_packages_num() const
{
	return _total_packages_num;
}
