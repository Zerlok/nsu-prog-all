#include <iostream>
#include <string>
using namespace std;

#include "imagepng.h"
#include "utils.h"


int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "First argument: name of .png image." << std::endl;
		std::cout << "Second argument: algorithm step (in degrees)." << std::endl;
		return 1;
	}

	ImagePNG src(argv[1]);

	int normalize_angle = pngutils::get_angle_of_horizontal(src, stoi(argv[2]));
	std::cout << "Normal angle is: " << normalize_angle << std::endl;

	pngfilters::build_rotated_image(src, src.get_width() / 2, src.get_height() / 2, normalize_angle).write("output.png");
	return 0;
}
