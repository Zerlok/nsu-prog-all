#include <string>
#include "media.h"


NormalMedia::NormalMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


NormalMedia::~NormalMedia()
{
}


DataPackage NormalMedia::get_modified_receiver_package(const DataPackage &package)
{
	return package;
}


DataPackage NormalMedia::get_modified_sender_package(const DataPackage &package)
{
	return package;
}


BitFailingMedia::BitFailingMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver),
	  _failbits_left_num((_sender_packages_num % 3) + 2)
{
}


BitFailingMedia::~BitFailingMedia()
{
}


DataPackage BitFailingMedia::get_modified_receiver_package(const DataPackage &package)
{
	if (!(rand() % 10)
			&& (_failbits_left_num > 0))
	{
		--_failbits_left_num;

		std::string data = package.get_data();
		data[(rand() % data.size())] = char(rand() % 256);

		return DataPackage(data);
	}

	return package;
}


DataPackage BitFailingMedia::get_modified_sender_package(const DataPackage &package)
{
	if (!(rand() % 10)
			&& (_failbits_left_num > 0))
	{
		--_failbits_left_num;

		std::string data = package.get_data();
		data[(rand() % data.size())] = char(rand() % 256);

		return DataPackage(data);
	}

	return package;
}


DisconnectionMedia::DisconnectionMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


DisconnectionMedia::~DisconnectionMedia()
{
}


bool DisconnectionMedia::simulate_transmission()
{
	DataPackage rpckg = _receiver.give_outgoing_package();
	_sender.take_incoming_package(rpckg);

	DataPackage spckg;
	while (!(_sender.is_stopped()))
		spckg = _sender.give_outgoing_package();

	return is_successed();
}
