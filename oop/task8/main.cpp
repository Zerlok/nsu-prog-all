#include <iostream>
using namespace std;

#include "imagepng.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	ImagePNG img(argv[1]);
	cout << "Opened image size: " << img.get_width() << "x" << img.get_height() << endl;

	ImagePNG::row_type &row = img[0];

	for (const auto row : img)
		cout << row << endl;

	ImagePNG::pixel p = img.get_pixel(0, 0);

	cout << "Pixel [0][0]: " << p << endl;

	return 0;
}
