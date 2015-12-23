#include <iostream>
#include <vector>
#include <png++/palette.hpp>
#include <math.h>

#include "utils.h"


template<typename T>
T count_percent(const T &a, const T &b)
{
	return ((a * 100) / b);
}


double get_radians(const int deg)
{
	static const double radian = M_PI / 180;
	return (deg * radian);
}


short pngutils::count_brightness(const ImagePNG::pixel_t &pixel)
{
	return (pngconsts::red_color_brightness_ratio * pixel.red
			+ pngconsts::green_color_brightness_ratio * pixel.green
			+ pngconsts::blue_color_brightness_ratio * pixel.blue);
}


int pngutils::count_average(const ImagePNG::pixel_t &p)
{
	return (p.red + p.green + p.blue) / 3;
}


ImagePNG pngfilters::build_grayscaled_image(const ImagePNG &img)
{
	ImagePNG graysclaed(img.get_width(), img.get_height());

	for (ImagePNG::const_iterator pit = img.cbegin();
		 pit != img.cend();
		 ++pit)
	{
		int average = pngutils::count_average(*pit);
		graysclaed.set_pixel(
				pit.get_x(),
				pit.get_y(),
				ImagePNG::pixel_t(average, average, average)
		);
	}

	return graysclaed;
}


std::vector<int> pngutils::get_histogram(const ImagePNG &img)
{
	std::vector<size_t> bins = std::vector<size_t>(pngconsts::palette_size, 0);
	std::vector<int> histogram;
	size_t max = 0;

	for (const ImagePNG::pixel_t pixel : img)
	{
		size_t i = pngutils::count_brightness(pixel);
		++bins[i];

		if (bins[i] > max)
			max = bins[i];
	}

	for (const size_t bin : bins)
		histogram.push_back(count_percent(bin, max));

	return histogram;
}


ImagePNG pngfilters::build_image_histogram(const ImagePNG &img)
{
	ImagePNG histogram_img(pngconsts::palette_size, pngconsts::histogram_height);
	std::vector<int> histogram = pngutils::get_histogram(img);

	for (size_t x = 0; x < histogram.size(); ++x)
		for (int y = (pngconsts::histogram_height - 1);
			 y >= int(pngconsts::histogram_height - histogram[x]);
			 --y)
			histogram_img.set_pixel(x, y, pngconsts::white_pixel);

	return histogram_img;
}


ImagePNG pngfilters::build_rotated_image(
		const ImagePNG &img,
		const int x0,
		const int y0,
		const int angle)
{
	const double alpha = get_radians(angle);
	const double sin_a = roundl(sin(alpha) * 1000.0) / 1000.0;
	const double cos_a = roundl(cos(alpha) * 1000.0) / 1000.0;

	size_t width = img.get_width();
	size_t height = img.get_height();
	ImagePNG rotated_img(width, height);

	for (ImagePNG::const_iterator pit = img.cbegin();
		 pit != img.cend();
		 ++pit)
	{
		const int dx = pit.get_x() - x0;
		const int dy = pit.get_y() - y0;
		const int x = (cos_a * dx - sin_a * dy) + x0;
		const int y = (sin_a * dx + cos_a * dy) + y0;

		ImagePNG::iterator it(x, y, &rotated_img);
		if (it.is_valid())
			it = (*pit);
	}

	return rotated_img;
}
