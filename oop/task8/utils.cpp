#include <iostream>
#include <algorithm>
#include <vector>
#include <png++/palette.hpp>

#include "affinetransformation.h"
#include "utils.h"


template<typename T>
T count_percent(const T &a, const T &b)
{
	return ((a * 100) / b);
}


short pngutils::count_pixel_intensity(const ImagePNG::pixel_t &pixel)
{
	return (pngconsts::red_color_brightness_ratio * pixel.red
			+ pngconsts::green_color_brightness_ratio * pixel.green
			+ pngconsts::blue_color_brightness_ratio * pixel.blue);
}


int pngutils::count_pixel_average_color(const ImagePNG::pixel_t &p)
{
	return (p.red + p.green + p.blue) / 3;
}


Histogram pngutils::get_histogram(const ImagePNG &img)
{
	std::vector<size_t> bins = std::vector<size_t>(pngconsts::palette_size, 0);
	Histogram histogram;
	size_t max = 0;

	for (const ImagePNG::pixel_t pixel : img)
	{
		size_t i = pngutils::count_pixel_intensity(pixel);
		++bins[i];

		if (bins[i] > max)
			max = bins[i];
	}

	for (size_t i = 0; i < bins.size(); ++i)
		histogram.push_back({count_percent(bins[i], max), i});

	return histogram;
}


Histogram pngutils::differentiate_histogram(const Histogram &histogram)
{
	Histogram differentiated;
	HistogramBin max = {0, 0};

	for (size_t i = 1; i < histogram.size(); ++i)
	{
		HistogramBin bin = {(histogram[i].first - histogram[i-1].first), i-1};
		differentiated.push_back(bin);

		if (bin > max)
			max = bin;
	}

	for (HistogramBin &bin : differentiated)
		bin.first = count_percent(bin.first, max.first);

	return differentiated;
}


size_t pngutils::count_intensity_leaps_in_rows(const ImagePNG &img, const int degrees)
{
	static const int intensity_threshold = pngconsts::palette_size / 2;
	size_t leaps_counter = 0;

	const size_t width = img.get_width();
	const size_t height = img.get_height();
	double dx = 1.0;
	double dy = 0.0;
	RotationTransformation(degrees).transform(dx, dy);

	double curr_x;
	double curr_y;
	double next_x;
	double next_y;

	// Rows from top edge.
	for (size_t row_begin_x = width - 1; int(row_begin_x) >= 0; --row_begin_x)
	{
		curr_x = row_begin_x;
		curr_y = 0.0;
		next_x = curr_x + dx;
		next_y = curr_y + dy;

		while ((int(curr_x) >= 0)
			   && (int(curr_y) >= 0)
			   && (int(next_x) >= 0)
			   && (int(next_y) >= 0)
			   && (int(curr_x) < int(width))
			   && (int(curr_y) < int(height))
			   && (int(next_x) < int(width))
			   && (int(next_y) < int(height)))
		{
			bool current_intensity = (count_pixel_intensity(img.get_pixel(curr_x, curr_y)) > intensity_threshold);
			bool next_intensity = (count_pixel_intensity(img.get_pixel(next_x, next_y)) > intensity_threshold);

			if (!(current_intensity == next_intensity))
				++leaps_counter;

			curr_x = next_x;
			curr_y = next_y;
			next_x += dx;
			next_y += dy;
		}
	}

	// Rows from left edge.
	for (size_t row_begin_y = 0; row_begin_y <= height; ++row_begin_y)
	{
		curr_x = 0.0;
		curr_y = row_begin_y;
		next_x = curr_x + dx;
		next_y = curr_y + dy;

		while ((int(curr_x) >= 0)
			   && (int(curr_y) >= 0)
			   && (int(next_x) >= 0)
			   && (int(next_y) >= 0)
			   && (int(curr_x) < int(width))
			   && (int(curr_y) < int(height))
			   && (int(next_x) < int(width))
			   && (int(next_y) < int(height)))
		{
			bool current_intensity = (count_pixel_intensity(img.get_pixel(curr_x, curr_y)) > intensity_threshold);
			bool next_intensity = (count_pixel_intensity(img.get_pixel(next_x, next_y)) > intensity_threshold);

			if (!(current_intensity == next_intensity))
				++leaps_counter;

			curr_x = next_x;
			curr_y = next_y;
			next_x += dx;
			next_y += dy;
		}
	}

	// Rows from bottom edge.
	for (size_t row_begin_x = 0; row_begin_x < width; ++row_begin_x)
	{
		curr_x = row_begin_x;
		curr_y = height;
		next_x = curr_x + dx;
		next_y = curr_y + dy;

		while ((int(curr_x) >= 0)
			   && (int(curr_y) >= 0)
			   && (int(next_x) >= 0)
			   && (int(next_y) >= 0)
			   && (int(curr_x) < int(width))
			   && (int(curr_y) < int(height))
			   && (int(next_x) < int(width))
			   && (int(next_y) < int(height)))
		{
			bool current_intensity = (count_pixel_intensity(img.get_pixel(curr_x, curr_y)) > intensity_threshold);
			bool next_intensity = (count_pixel_intensity(img.get_pixel(next_x, next_y)) > intensity_threshold);

			if (!(current_intensity == next_intensity))
				++leaps_counter;

			curr_x = next_x;
			curr_y = next_y;
			next_x += dx;
			next_y += dy;
		}
	}

	return leaps_counter;
}


int pngutils::get_angle_of_horizontal(const ImagePNG &img, const int degrees_step)
{
	Histogram histogram = pngutils::get_histogram(img);
	pngfilters::build_histogram(histogram).write("histogram.out.png");

	Histogram diff_histogram = pngutils::differentiate_histogram(histogram);
	sort(diff_histogram.begin(), diff_histogram.end());

	ImagePNG bin_img = pngfilters::build_thresholded_image(
			img,
			double(diff_histogram.back().second) / pngconsts::palette_size
	);
	bin_img.write("binary.out.png");

	std::vector<std::pair<size_t, int> > leaps;
	for (int alpha = -90; alpha <= 90; alpha += degrees_step)
	{
		size_t row_leaps = pngutils::count_intensity_leaps_in_rows(bin_img, alpha);

		if (row_leaps > 0)
		{
			leaps.push_back({row_leaps, alpha});
			std::cout << "Angle: " << leaps.back().second << " degrees, " << leaps.back().first << " leaps." << std::endl;
		}
	}

	std::sort(leaps.begin(), leaps.end());
	return leaps.front().second;
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

	return graysclaed;
}


ImagePNG pngfilters::build_histogram(const Histogram &histogram)
{
	ImagePNG histogram_img(histogram.size(), pngconsts::histogram_height);

	for (const HistogramBin &bin : histogram)
		for (int y = (pngconsts::histogram_height - 1);
			 y >= int(pngconsts::histogram_height - bin.first);
			 --y)
			histogram_img.set_pixel(bin.second, y, pngconsts::white_pixel);

	return histogram_img;
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

	return thresholded_img;
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
