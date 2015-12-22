#include <iostream>
#include "utils.h"


int percent_of(int a, int b)
{
	return  a * 100 / b;
}


short pngutils::count_brightness(const ImagePNG::pixel &pixel)
{
	return (pngconsts::red_color_brightness_ratio * pixel.red
			+ pngconsts::green_color_brightness_ratio * pixel.green
			+ pngconsts::blue_color_brightness_ratio * pixel.blue);
}


ImagePNG::pixel pngutils::count_average(const ImagePNG::pixel &p)
{
	int average = (p.red + p.green + p.blue) / 3;
	return ImagePNG::pixel(average, average, average);
}


ImagePNG pngfilters::get_grayscaled(const ImagePNG &img)
{
	ImagePNG graysclaed(img.get_width(), img.get_height());
	ImagePNG::const_iterator pit;
	try
	{
		for (pit = img.begin();
			 pit != img.end();
			 ++pit)
			graysclaed.set_pixel(pit.get_x(), pit.get_y(), pngutils::count_average(*pit));
	}
	catch (std::out_of_range)
	{
		std::cerr << "Invalid pixel iterator: " << pit << " "
				  << percent_of(pit.get_num(), last_pixel_num)
				  << std::endl;
		return img;
	}

	return graysclaed;
}

ImagePNG pngfilters::get_histogram(const ImagePNG &img)
{

}
