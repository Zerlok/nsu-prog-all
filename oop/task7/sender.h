#ifndef __SENDER_H__
#define __SENDER_H__


#include <vector>
#include <string>
#include "datapackage.h"
#include "xprotocol.h"


class Sender
{
	public:
		Sender(const std::string &data);
		~Sender();

		enum class Status
		{
			disconnected = 0,
			data_transmission_finished,
			package_sending_succeessful,
			package_sending_failed,
			incoming_package_receiving_failed,
			incoming_command_unpacking_failed,
			connection_lost
		};

		const Status &get_status() const;
		bool is_stopped() const;

		const DataPackage &give_outgoing_package() const;
		void take_incoming_package(const DataPackage &package);

		int get_left_packages_num() const;

	private:
		static const DataPackage success_cmd_pckg;
		static const DataPackage fail_cmd_pckg;

		std::vector<DataPackage> _packages;
		int _fails_in_row_counter;
		Status _status;
};


// __SENDER_H__
#endif
