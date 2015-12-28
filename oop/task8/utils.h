#ifndef __IMAGEPNG_UTILS_H__
#define __IMAGEPNG_UTILS_H__


#include <vector>
#include "imagepng.h"


using HistogramBin = std::pair<int, int>;
using Histogram = std::vector<HistogramBin>;
//using


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
	short count_intensity(const ImagePNG::pixel_t &pixel);
	int count_average_color(const ImagePNG::pixel_t &p);
	Histogram get_histogram(const ImagePNG &img);
	Histogram differentiate_histogram(const Histogram &histogram);
	size_t count_intensity_leaps(const ImagePNG::const_iterator &it, const int degrees);
}


namespace pngfilters
{
	ImagePNG build_histogram(const Histogram &histogram);
	ImagePNG build_grayscaled_image(const ImagePNG &img);
	ImagePNG build_thresholded_image(const ImagePNG &img, const double threshold);
	ImagePNG build_rotated_image(const ImagePNG &img, const int x0, const int y0, const int angle);
	ImagePNG build_normalized_image(const ImagePNG &img);
}


// __IMAGEPNG_UTILS_H__
#endif
