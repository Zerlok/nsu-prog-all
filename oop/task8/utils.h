#ifndef __IMAGEPNG_UTILS_H__
#define __IMAGEPNG_UTILS_H__


#include "imagepng.h"


namespace pngconsts
{
	static const float red_color_brightness_ratio = 0.30;
	static const float green_color_brightness_ratio = 0.59;
	static const float blue_color_brightness_ratio = 0.11;
}


namespace pngutils
{
	short count_brightness(const ImagePNG::pixel &pixel);
	ImagePNG::pixel count_average(const ImagePNG::pixel &p);
}


namespace pngfilters
{
	ImagePNG get_grayscaled(const ImagePNG &img);
	ImagePNG get_histogram(const ImagePNG &img);
}


// __IMAGEPNG_UTILS_H__
#endif
