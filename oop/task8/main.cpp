#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "imagepng.h"
#include "utils.h"


int main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;

	ImagePNG src(argv[1]);
	cout << "Opened image size: " << src.get_width() << "x" << src.get_height() << " WxH"
		 << " = " << src.get_size() << " pixels in total" << endl
		 << "End: " << src.end()
		 << endl;

	ImagePNG img = pngfilters::build_rotated_image(src, src.get_width()/2, src.get_height()/2, stoi(argv[2]));
	img.write("output.png");

	return 0;
}
