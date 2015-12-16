#include "sender.h"


const DataPackage Sender::success_cmd_pckg = DataPackage(xmodem_protocol::successed_transmission_cmd);
const DataPackage Sender::fail_cmd_pckg = DataPackage(xmodem_protocol::failed_transmitting_cmd);


Sender::Sender(const std::string &data)
	: _sending_data(data),
	  _packages(),
	  _tries_counter(0),
	  _status(Status::disconnected)
{
	int blocks_num = int(data.size()) / DataPackage::max_data_len;

	// Create data blocks of max data length size.
	for (int i = 0; i < blocks_num; ++i)
	{
		const std::string &data_block = data.substr(
				i * DataPackage::max_data_len,
				DataPackage::max_data_len
		);
		_packages.push_back(DataPackage(data_block));
	}

	// If some data left outside of data block - place it into package.
	if (int(data.size()) % DataPackage::max_data_len)
	{
		const std::string &last_block = data.substr(
				blocks_num * DataPackage::max_data_len,
				DataPackage::max_data_len
		);
		_packages.push_back(DataPackage(last_block));
	}

	// Insert additional package about sending data (number of sending blocks).
	_packages.insert(
			_packages.begin(),
			DataPackage(int(_packages.size()))
	);
}


Sender::~Sender()
{
}


const Sender::Status &Sender::get_status() const
{
	return _status;
}


bool Sender::is_connected() const
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return false;

		case Status::package_sending_successful:
		case Status::package_sending_failed:
		case Status::incoming_package_receiving_failed:
		case Status::incoming_command_invalid:
		default:
			return true;
	}
}


bool Sender::is_stopped() const
{
	switch (_status)
	{
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return true;

		case Status::disconnected:
		case Status::package_sending_successful:
		case Status::package_sending_failed:
		case Status::incoming_package_receiving_failed:
		case Status::incoming_command_invalid:
		default:
			return false;
	}
}


const DataPackage &Sender::give_outgoing_package()
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::package_sending_successful:
		case Status::package_sending_failed:
			++_tries_counter;
			return _packages.front();

		case Status::data_transmission_finished:
			return success_cmd_pckg;

		case Status::incoming_package_receiving_failed:
		case Status::incoming_command_invalid:
		case Status::connection_lost:
		default:
			++_tries_counter;
			return fail_cmd_pckg;
	}
}


void Sender::take_incoming_package(const DataPackage &package)
{
	if (is_stopped())
		return;

	if (!package.is_valid())
	{
		_status = ((_tries_counter < xmodem_protocol::max_tries)
				   ? Status::incoming_package_receiving_failed
				   : Status::connection_lost);
		return;
	}

	// Unpack command.
	const std::string &income_data = package.get_data();
	size_t success_cmd_pos = income_data.find(xmodem_protocol::successed_transmission_cmd);
	size_t fail_cmd_pos = income_data.find(xmodem_protocol::failed_transmitting_cmd);

	if (success_cmd_pos != std::string::npos)
	{
		_tries_counter = 0;
		_packages.erase(_packages.begin());
		_status = ((!_packages.empty())
					? Status::package_sending_successful
					: Status::data_transmission_finished);
	}
	else if (fail_cmd_pos != std::string::npos)
		_status = Status::package_sending_failed;

	else // incoming comand is invalid.
		_status = Status::incoming_command_invalid;

	// Update status using fails and left packages.
	if (_tries_counter >= xmodem_protocol::max_tries)
		_status = Status::connection_lost;
}


const std::string &Sender::get_sending_data() const
{
	return _sending_data;
}


int Sender::get_left_packages_num() const
{
	return _packages.size();
}


std::ostream &operator<<(std::ostream &out, const Sender::Status &status)
{
	switch (status)
	{
		case Sender::Status::disconnected:
			out << "[disconnected]";
			break;

		case Sender::Status::data_transmission_finished:
			out << "[data transmission finished]";
			break;

		case Sender::Status::package_sending_successful:
			out << "[package sending successful]";
			break;

		case Sender::Status::package_sending_failed:
			out << "[package sending failed]";
			break;

		case Sender::Status::incoming_package_receiving_failed:
			out << "[incoming package receiving failed]";
			break;

		case Sender::Status::incoming_command_invalid:
			out << "[incoming command invalid]";
			break;

		case Sender::Status::connection_lost:
		default:
			out << "[connection lost]";
			break;
	}

	return out;
}

