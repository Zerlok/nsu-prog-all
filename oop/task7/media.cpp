#include <string>
#include "media.h"


NormalMedia::NormalMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


NormalMedia::~NormalMedia()
{
}


bool NormalMedia::emulate_transmission()
{
	int total_packages_num = _sender.get_left_packages_num();
	for (int i = 0; i < total_packages_num + 1; ++i)
	{
		const DataPackage &rpckg = _receiver.give_outgoing_package();
		_sender.take_incoming_package(rpckg);
		const DataPackage &spckg = _sender.give_outgoing_package();
		_receiver.take_incoming_package(spckg);
	}

	_result = ((_sender.get_status() == Sender::Status::data_transmission_finished)
			   && (_receiver.get_status() == Receiver::Status::data_transmission_finished)
			   && (_sender.get_left_packages_num() == 0)
			   && (_receiver.get_total_packages_num() == total_packages_num - 1)
			   && (_receiver.get_received_packages_num() == total_packages_num - 1)
			   && (_sender.get_sending_data() == _receiver.get_received_data()));

	return _result;
}


BitFailingMedia::BitFailingMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


BitFailingMedia::~BitFailingMedia()
{
}


bool BitFailingMedia::emulate_transmission()
{
	int total_packages_num;
	std::cout << _sender.get_status() << " " << Sender::Status::data_transmission_finished << std::endl;
	std::cout << _receiver.get_status() << " " << Receiver::Status::data_transmission_finished << std::endl;
	std::cout << _receiver.get_total_packages_num() << " " << total_packages_num - 1<< std::endl;
	std::cout << _receiver.get_received_packages_num() << " " << total_packages_num - 1 << std::endl;
	std::cout << _sender.get_left_packages_num() << std::endl;
	std::cout << "Sent: " << _sender.get_sending_data() << std::endl;
	std::cout << "Received: " << _receiver.get_received_data() << std::endl;
	return false;
}


DisconnectionMedia::DisconnectionMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


DisconnectionMedia::~DisconnectionMedia()
{
}


bool DisconnectionMedia::emulate_transmission()
{
	int total_packages_num;
	std::cout << _sender.get_status() << " " << Sender::Status::data_transmission_finished << std::endl;
	std::cout << _receiver.get_status() << " " << Receiver::Status::data_transmission_finished << std::endl;
	std::cout << _receiver.get_total_packages_num() << " " << total_packages_num - 1<< std::endl;
	std::cout << _receiver.get_received_packages_num() << " " << total_packages_num - 1 << std::endl;
	std::cout << _sender.get_left_packages_num() << std::endl;
	std::cout << "Sent: " << _sender.get_sending_data() << std::endl;
	std::cout << "Received: " << _receiver.get_received_data() << std::endl;
	return true;
}
