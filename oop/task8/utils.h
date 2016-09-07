#ifndef __IMAGEPNG_UTILS_H__
#define __IMAGEPNG_UTILS_H__


#include <vector>
#include "imagepng.h"
#include "histogram.h"


using ImgHistogram = Histogram<size_t, int>;


namespace pngconsts
{
	static const float red_color_brightness_ratio = 0.30;
	static const float green_color_brightness_ratio = 0.59;
	static const float blue_color_brightness_ratio = 0.11;

	static const size_t palette_size = 256;
	static const size_t default_histogram_height = 100;

	static const png::rgb_pixel black_pixel = png::rgb_pixel(0, 0, 0);
	static const png::rgb_pixel white_pixel = png::rgb_pixel(palette_size - 1, palette_size - 1, palette_size - 1);
}


namespace pngutils
{
	int count_pixel_intensity(const ImagePNG::pixel_t &pixel);
	int count_pixel_average_color(const ImagePNG::pixel_t &pixel);
	ImgHistogram get_histogram(const ImagePNG &img);
	size_t count_intensity_leaps_in_rows(const ImagePNG &img, const int degrees);
	int get_angle_of_horizontal(const ImagePNG &img, const int degrees_step = 10);
}


namespace pngfilters
{
	ImagePNG build_histogram(const ImgHistogram &histogram);
	ImagePNG build_grayscaled_image(const ImagePNG &img);
	ImagePNG build_thresholded_image(const ImagePNG &img, const double threshold);
	ImagePNG build_rotated_image(const ImagePNG &img, const int x0, const int y0, const int angle);
}


// __IMAGEPNG_UTILS_H__
#endif
