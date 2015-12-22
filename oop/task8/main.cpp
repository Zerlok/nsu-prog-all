#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "imagepng.h"
#include "utils.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	ImagePNG src(argv[1]);
	cout << "Opened image size: " << src.get_width() << "x" << src.get_height() << " WxH"
		 << " = " << src.get_width() * src.get_height() << " pixels in total"
		 << endl;
	cout << "End: " << src.end() << endl;

	ImagePNG img = pngfilters::get_grayscaled(src);
	img.write("output.png");
	return 0;
}
