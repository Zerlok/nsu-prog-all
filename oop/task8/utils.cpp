#include <iostream>
#include <vector>
#include <png++/palette.hpp>

#include "affinetransformation.h"
#include "utils.h"


template<typename T>
T count_percent(const T &a, const T &b)
{
	return ((a * 100) / b);
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
	// Create affine transformation matrix.
	RotationTransformation rot(angle);
	rot += TranslationTransformation(x0, y0);

	const size_t width = img.get_width();
	const size_t height = img.get_height();

	// Count image size.
	double a = -y0;
	double c = -x0;
	double b = width - x0;
	double d = height - y0;

	rot.transform(-x0, a);
	rot.transform(c, -y0);
	rot.transform(b, height - y0);
	rot.transform(width - x0, d);
	const double dx = (b - a) / 2;
	const double dy = (d - c) / 2;

	rot += TranslationTransformation(dx / 2, dy / 2);
	ImagePNG rotated_img(dx + width, dy + height);

	// Do affine transformation for each pixel;
	for (ImagePNG::const_iterator pit = img.cbegin();
		 pit != img.cend();
		 ++pit)
	{
		double x = pit.get_x() - x0;
		double y = pit.get_y() - y0;
		rot.transform(x, y);

		ImagePNG::iterator it(x, y, &rotated_img);
		if (it.is_valid())
			it = (*pit);
	}

	return rotated_img;
}
