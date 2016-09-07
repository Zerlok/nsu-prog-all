#ifndef __MEDIA_H__
#define __MEDIA_H__


#include "sender.h"
#include "receiver.h"
#include <unistd.h>
#include <time.h>


class AbstractMedia
{
	public:
		AbstractMedia(Sender &sender, Receiver &receiver)
			: _sender_packages_num(sender.get_left_packages_num()),
			  _sender(sender),
			  _receiver(receiver)
		{
			srand(time(NULL));
		}
		virtual ~AbstractMedia() {}

		virtual bool simulate_transmission()
		{
			while (!(_sender.is_stopped()))
			{
				const DataPackage &rpckg = _receiver.give_outgoing_package();
				const DataPackage &modified_rpckg = get_modified_receiver_package(rpckg);
				_sender.take_incoming_package(modified_rpckg);
				after_sender_took_answer();

				const DataPackage &spckg = _sender.give_outgoing_package();
				const DataPackage &modified_spckg = get_modified_sender_package(spckg);
				_receiver.take_incoming_package(modified_spckg);
				after_receiver_took_answer();
			}

			return is_successed();
		}

		virtual DataPackage get_modified_receiver_package(const DataPackage &package) { return package; }
		virtual DataPackage get_modified_sender_package(const DataPackage &package) { return package; }
		virtual bool is_successed() const
		{
			return ((_sender.get_status() == Sender::Status::data_transmission_finished)
					&& (_receiver.get_status() == Receiver::Status::data_transmission_finished)
					&& (_sender.get_left_packages_num() == 0)
					&& (_receiver.get_total_packages_num() == _sender_packages_num - 1)
					&& (_receiver.get_received_packages_num() == _sender_packages_num - 1)
					&& (_sender.get_sending_data() == _receiver.get_received_data()));
		}

		virtual void after_sender_took_answer() {}
		virtual void after_receiver_took_answer() {}

	protected:
		const int _sender_packages_num;
		Sender &_sender;
		Receiver &_receiver;
};


class NormalMedia : public AbstractMedia
{
	public:
		NormalMedia(Sender &sender, Receiver &receiver);
		~NormalMedia();

		DataPackage get_modified_receiver_package(const DataPackage &package) override;
		DataPackage get_modified_sender_package(const DataPackage &package) override;
};


class BitFailingMedia : public AbstractMedia
{
	public:
		BitFailingMedia(Sender &sender, Receiver &receiver);
		~BitFailingMedia();

		DataPackage get_modified_receiver_package(const DataPackage &package) override;
		DataPackage get_modified_sender_package(const DataPackage &package) override;

	private:
		int _failbits_left_num;
};


class DisconnectionMedia : public AbstractMedia
{
	public:
		DisconnectionMedia(Sender &sender, Receiver &receiver);
		~DisconnectionMedia();

		virtual bool simulate_transmission() override;
};


// __MEDIA_H__
#endif
