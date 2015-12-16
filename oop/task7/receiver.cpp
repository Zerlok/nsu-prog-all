#include <sstream>
#include "receiver.h"


const DataPackage Receiver::success_cmd_pckg = DataPackage(xmodem_protocol::successed_transmission_cmd);
const DataPackage Receiver::fail_cmd_pckg = DataPackage(xmodem_protocol::failed_transmitting_cmd);


Receiver::Receiver()
	: _packages(),
	  _tries_counter(0),
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


bool Receiver::is_connected() const
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return false;

		case Status::package_receiving_succeessful:
		case Status::package_receiving_failed:
		case Status::outgoing_command_sending_failed:
		default:
			return true;
	}
}


bool Receiver::is_stopped() const
{
	switch (_status)
	{
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return true;

		case Status::disconnected:
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
	if (_status == Status::data_transmission_finished)
		return;

	if (!package.is_valid())
	{
		++_tries_counter;
		_status = ((_tries_counter < xmodem_protocol::max_tries)
				   ? Status::package_receiving_failed
				   : Status::connection_lost);
		return;
	}

	const std::string &income_data = package.get_data();
	size_t fail_cmd_pos = income_data.find(xmodem_protocol::failed_transmitting_cmd);

	if (fail_cmd_pos != std::string::npos)
	{
		++_tries_counter;
		_status = ((_tries_counter < xmodem_protocol::max_tries)
				   ? Status::outgoing_command_sending_failed
				   : Status::connection_lost);
	}
	else // Save received data block.
	{
		if (_total_packages_num > 0)
			_packages.push_back(package);
		else // Set total packages num.
			_total_packages_num = std::stoi(package.get_data());

		_tries_counter = 0;
		_status	= ((get_received_packages_num() < _total_packages_num)
				   ? Status::package_receiving_succeessful
				   : Status::data_transmission_finished);
	}
}


std::string Receiver::get_received_data() const
{
	if (get_received_packages_num() != _total_packages_num)
		return "";

	std::string total_data = "";
	for (const DataPackage &package : _packages)
		total_data.append(package.get_data());

	return total_data;
}


int Receiver::get_received_packages_num() const
{
	return _packages.size();
}


int Receiver::get_total_packages_num() const
{
	return _total_packages_num;
}


std::ostream &operator<<(std::ostream &out, const Receiver::Status &status)
{
	switch (status)
	{
		case Receiver::Status::disconnected:
			out << "[disconnected]";
			break;

		case Receiver::Status::data_transmission_finished:
			out << "[data transmission finished]";
			break;

		case Receiver::Status::package_receiving_succeessful:
			out << "[package receiving successful]";
			break;

		case Receiver::Status::package_receiving_failed:
			out << "[package receiving failed]";
			break;

		case Receiver::Status::outgoing_command_sending_failed:
			out << "[outgoing command sending failed]";
			break;

		case Receiver::Status::connection_lost:
		default:
			out << "[connection lost]";
			break;
	}

	return out;
}
