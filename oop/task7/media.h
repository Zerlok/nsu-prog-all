#ifndef __MEDIA_H__
#define __MEDIA_H__


#include "sender.h"
#include "receiver.h"


class AbstractMedia
{
	public:
		AbstractMedia(Sender &sender, Receiver &receiver)
			: _sender(sender),
			  _receiver(receiver),
			  _result(false) {}
		virtual ~AbstractMedia() {}
		virtual bool emulate_transmission() = 0;
		bool get_result() const { return _result; }

	protected:
		Sender &_sender;
		Receiver &_receiver;
		bool _result;
};


class NormalMedia : public AbstractMedia
{
	public:
		NormalMedia(Sender &sender, Receiver &receiver);
		~NormalMedia();

		bool emulate_transmission() override;
};


class BitFailingMedia : public AbstractMedia
{
	public:
		BitFailingMedia(Sender &sender, Receiver &receiver);
		~BitFailingMedia();

		bool emulate_transmission() override;
};


class DisconnectionMedia : public AbstractMedia
{
	public:
		DisconnectionMedia(Sender &sender, Receiver &receiver);
		~DisconnectionMedia();

		bool emulate_transmission() override;
};


// __MEDIA_H__
#endif
