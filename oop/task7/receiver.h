#ifndef __RECEIVER_H__
#define __RECEIVER_H__


#include <vector>
#include <string>
#include "datapackage.h"
#include "xprotocol.h"


class Receiver
{
	public:
		Receiver();
		~Receiver();

		enum class Status
		{
			disconnected = 0,
			data_transmission_finished,
			package_receiving_succeessful,
			package_receiving_failed,
			outgoing_command_sending_failed,
			connection_lost
		};

		const Status &get_status() const;
		bool is_connected() const;
		bool is_stopped() const;

		const DataPackage &give_outgoing_package();
		void take_incoming_package(const DataPackage &package);

		std::string get_received_data() const;
		int get_received_packages_num() const;
		int get_total_packages_num() const;

	private:
		static const DataPackage success_cmd_pckg;
		static const DataPackage fail_cmd_pckg;

		std::vector<DataPackage> _packages;
		int _tries_counter;
		int _total_packages_num;
		DataPackage _outgoing_cmd;
		Status _status;
};


std::ostream &operator<<(std::ostream &out, const Receiver::Status &status);


// __RECEIVER_H__
#endif
