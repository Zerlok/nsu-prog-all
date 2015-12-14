#include "media.h"


NormalMedia::NormalMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


NormalMedia::~NormalMedia()
{
}


void NormalMedia::emulate_transmission()
{

}


BitFailingMedia::BitFailingMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


BitFailingMedia::~BitFailingMedia()
{
}


void BitFailingMedia::emulate_transmission()
{

}


DisconnectionMedia::DisconnectionMedia(Sender &sender, Receiver &receiver)
	: AbstractMedia(sender, receiver)
{
}


DisconnectionMedia::~DisconnectionMedia()
{
}


void DisconnectionMedia::emulate_transmission()
{

}
