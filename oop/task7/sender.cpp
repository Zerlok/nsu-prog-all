#include "sender.h"


const DataPackage Sender::success_cmd_pckg = DataPackage(xmodem_protocol::successed_transmission_cmd);
const DataPackage Sender::fail_cmd_pckg = DataPackage(xmodem_protocol::failed_transmitting_cmd);


Sender::Sender(const std::string &data)
	: _packages(),
	  _fails_in_row_counter(0),
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


bool Sender::is_stopped() const
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::data_transmission_finished:
		case Status::connection_lost:
			return true;

		case Status::package_sending_succeessful:
		case Status::package_sending_failed:
		case Status::incoming_package_receiving_failed:
		case Status::incoming_command_unpacking_failed:
		default:
			return false;
	}
}


const DataPackage &Sender::give_outgoing_package() const
{
	switch (_status)
	{
		case Status::disconnected:
		case Status::package_sending_succeessful:
		case Status::package_sending_failed:
			return _packages.front();

		case Status::data_transmission_finished:
			return success_cmd_pckg;

		case Status::incoming_package_receiving_failed:
		case Status::incoming_command_unpacking_failed:
		case Status::connection_lost:
		default:
			return fail_cmd_pckg;
	}
}


void Sender::take_incoming_package(const DataPackage &package)
{
	if (!package.is_valid())
	{
		++_fails_in_row_counter;
		_status = ((_fails_in_row_counter < xmodem_protocol::max_fails_in_row_num)
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
		_fails_in_row_counter = 0;
		_packages.erase(_packages.begin());
		_status = ((!_packages.empty())
					? Status::package_sending_succeessful
					: Status::data_transmission_finished);
	}
	else if (fail_cmd_pos != std::string::npos)
	{
		++_fails_in_row_counter;
		_status = Status::package_sending_failed;
	}
	else
	{
		++_fails_in_row_counter;
		_status = Status::incoming_command_unpacking_failed;
	}

	// Update status using fails and left packages.
	if (_fails_in_row_counter >= xmodem_protocol::max_fails_in_row_num)
		_status = Status::connection_lost;
}


int Sender::get_left_packages_num() const
{
	return _packages.size();
}
