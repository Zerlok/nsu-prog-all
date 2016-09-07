#include <iostream>
#include <png++/palette.hpp>
#include <sstream>

#include "affinetransformation.h"
#include "imageleapscounter.h"
#include "utils.h"


int pngutils::count_pixel_intensity(const ImagePNG::pixel_t &pixel)
{
	return (pngconsts::red_color_brightness_ratio * pixel.red
			+ pngconsts::green_color_brightness_ratio * pixel.green
			+ pngconsts::blue_color_brightness_ratio * pixel.blue);
}


int pngutils::count_pixel_average_color(const ImagePNG::pixel_t &pixel)
{
	return (pixel.red + pixel.green + pixel.blue) / 3;
}


ImgHistogram pngutils::get_histogram(const ImagePNG &img)
{
	ImgHistogram histogram(pngconsts::palette_size);

	for (const ImagePNG::pixel_t pixel : img)
		++histogram[pngutils::count_pixel_intensity(pixel)];

	return histogram;
}


bool count_leap(const ImagePNG::pixel_t &pixel)
{
	static const int threshold = pngconsts::palette_size / 2;
	return (pngutils::count_pixel_intensity(pixel) > threshold);
}


int pngutils::get_angle_of_horizontal(const ImagePNG &img, const int degrees_step)
{
	const ImgHistogram histogram = pngutils::get_histogram(img);
	pngfilters::build_histogram(histogram).write("histogram.out.png");

	ImgHistogram diff_histogram = histogram.differentiate();

	ImagePNG bin_img = pngfilters::build_thresholded_image(
			img,
			double(diff_histogram.get_max_bin().pos) / pngconsts::palette_size
	);
	bin_img.write("binary.out.png");

	ImageLeapsCounter leaps_counter(bin_img);
	for (int alpha = -90; alpha <= 90; alpha += degrees_step)
	{
		leaps_counter.set_direction(alpha);
		ImgHistogram leaps_histogram = leaps_counter.count_leaps_to_histogram(count_leap);

		std::stringstream ss;
		ss << "leapshisto" << alpha << ".out.png";
		pngfilters::build_histogram(leaps_histogram).write(ss.str());

		leaps_counter.reset();
	}

	return 0;
}


ImagePNG pngfilters::build_grayscaled_image(const ImagePNG &img)
{
	ImagePNG graysclaed(img.get_width(), img.get_height());

	for (ImagePNG::const_iterator pit = img.cbegin();
		 pit != img.cend();
		 ++pit)
	{
		int average = pngutils::count_pixel_average_color(*pit);
		graysclaed.set_pixel(
				pit.get_x(),
				pit.get_y(),
				ImagePNG::pixel_t(average, average, average)
		);
	}

	return std::move(graysclaed);
}


ImagePNG pngfilters::build_histogram(const ImgHistogram &histogram)
{
	ImagePNG histogram_img(histogram.size(), pngconsts::default_histogram_height);
	ImgHistogram histo = histogram.in_percents();

	for (const ImgHistogram::Bin &bin : histo)
		for (int y = (pngconsts::default_histogram_height - 1);
			 y >= int(pngconsts::default_histogram_height - bin.height);
			 --y)
			histogram_img.set_pixel(bin.pos, y, pngconsts::white_pixel);

	return std::move(histogram_img);
}


ImagePNG pngfilters::build_thresholded_image(const ImagePNG &img, const double threshold)
{
	ImagePNG thresholded_img(img.get_width(), img.get_height());

	for (ImagePNG::const_iterator it = img.cbegin();
		 it != img.cend();
		 ++it)
	{
		thresholded_img.set_pixel(
				it.get_x(),
				it.get_y(),
				(((pngutils::count_pixel_intensity(*it) / 255.0) > threshold)
					? pngconsts::white_pixel
					: pngconsts::black_pixel
				)
		);
	}

	return std::move(thresholded_img);
}


ImagePNG pngfilters::build_rotated_image(
		const ImagePNG &img,
		const int x0,
		const int y0,
		const int angle)
{
	ImagePNG rotated_img(img.get_width(), img.get_height());

	// Create affine transformation.
	RotationTransformation rotated_coordinates = RotationTransformation(-angle);
	rotated_coordinates += TranslationTransformation(x0, y0);
	TranslationTransformation local_coordinates(-x0, -y0);

	// Do affine transformation for each pixel;
	for (ImagePNG::iterator pit = rotated_img.begin();
		 pit != rotated_img.end();
		 ++pit)
	{
		double x = pit.get_x();
		double y = pit.get_y();

		local_coordinates.transform(x, y);
		rotated_coordinates.transform(x, y);

		ImagePNG::const_iterator it(x, y, &img);
		if (it.is_valid())
			pit = (*it);
	}

	return std::move(rotated_img);
}
