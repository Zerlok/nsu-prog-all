#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "media.h"
#include "factory.h"
#include "xprotocol.h"
using namespace std;
using MediaFactory = Factory<std::string, AbstractMedia>;

void help(char *exec_name, const MediaFactory &media_factory)
{
	cout << "Usage: " << exec_name << " [MEDIA] [INPUT FILE] [OUTPUT FILE]" << endl;

	cout << "   MEDIA - type of media (on of: ";
	const vector<MediaFactory::Id> &registrated_classes = media_factory.get_registrated();
	copy(registrated_classes.begin(), registrated_classes.end(), std::ostream_iterator<MediaFactory::Id>(cout, " "));
	cout << ")" << endl;

	cout << "   INPUT FILE - file with incoming data to transfer." << endl;
	cout << "   OUTPUT FILE - file where the data will be transfered to." << endl;
}

//	MediaFactory media_factory;
//	media_factory.register_class<NormalMedia>("normal");
//	media_factory.register_class<BitFailingMedia>("bitfailing");
//	media_factory.register_class<DisconnectionMedia>("disconnecting");
//		help(argv[0], media_factory);

int main(int argc, char **argv)
{
	if (argc != 1)
		return 1;

	Sender s(xmodem_utils::read_all_input("normal-media-test.txt"));
//	Sender s("Hello world!");
	Receiver r;
	NormalMedia media(s, r);

	cout << media.emulate_transmission() << endl;

	return 0;
}
