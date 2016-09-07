#include <iostream>

#include "sender.h"
#include "receiver.h"
#include "media.h"
#include "xprotocol.h"


using namespace std;


int main(int argc, char **argv)
{
	if (argc != 1)
		return 1;

	Sender s(xmodem_utils::read_all_input("normal-media-test.txt"));
	Receiver r;
	BitFailingMedia media(s, r);

	media.simulate_transmission();

	return (!media.is_successed());
}
