#ifndef __MEDIA_H__
#define __MEDIA_H__


#include "sender.h"
#include "receiver.h"


class AbstractMedia
{
	public:
		AbstractMedia(Sender &sender, Receiver &receiver)
			: _sender(sender),
			  _receiver(receiver) {}
		virtual ~AbstractMedia() {}
		virtual void emulate_transmission() = 0;

	protected:
		Sender &_sender;
		Receiver &_receiver;
};


class NormalMedia : public AbstractMedia
{
	public:
		NormalMedia(Sender &sender, Receiver &receiver);
		~NormalMedia();

		void emulate_transmission() override;
};


class BitFailingMedia : public AbstractMedia
{
	public:
		BitFailingMedia(Sender &sender, Receiver &receiver);
		~BitFailingMedia();

		void emulate_transmission() override;
};


class DisconnectionMedia : public AbstractMedia
{
	public:
		DisconnectionMedia(Sender &sender, Receiver &receiver);
		~DisconnectionMedia();

		void emulate_transmission() override;
};


// __MEDIA_H__
#endif
