#ifndef __IMAGEPNG_UTILS_H__
#define __IMAGEPNG_UTILS_H__


#include "imagepng.h"


namespace pngconsts
{
	static const float red_color_brightness_ratio = 0.30;
	static const float green_color_brightness_ratio = 0.59;
	static const float blue_color_brightness_ratio = 0.11;

	static const size_t palette_size = 256;
	static const size_t histogram_height = 100;

	static const png::rgb_pixel black_pixel = png::rgb_pixel(0, 0, 0);
	static const png::rgb_pixel white_pixel = png::rgb_pixel(
			palette_size - 1,
			palette_size - 1,
			palette_size - 1
	);
}


namespace pngutils
{
	short count_brightness(const ImagePNG::pixel_t &pixel);
	int count_average(const ImagePNG::pixel_t &p);
	std::vector<int> get_histogram(const ImagePNG &img);
}


namespace pngfilters
{
	ImagePNG build_grayscale_image(const ImagePNG &img);
	ImagePNG build_histogram_image(const ImagePNG &img);
}


// __IMAGEPNG_UTILS_H__
#endif
