#include "affinetransformation.h"
#include "imageleapscounter.h"


const double ImageLeapsCounter::_default_dx = 1.0;
const double ImageLeapsCounter::_default_dy = 0.0;


ImageLeapsCounter::ImageLeapsCounter(const ImagePNG &img)
	: img(img),
	  width(img.get_width()),
	  height(img.get_height()),
	  _dx(_default_dx),
	  _dy(_default_dy),
	  _leaps_num(0),
	  _rows_num(0)
{
}


ImageLeapsCounter::~ImageLeapsCounter()
{
}


void ImageLeapsCounter::set_direction(const int degrees)
{
	_dx = _default_dx;
	_dy = _default_dy;

	RotationTransformation(degrees).transform(_dx, _dy);
}


size_t ImageLeapsCounter::get_counted_leaps() const
{
	return _leaps_num;
}


size_t ImageLeapsCounter::get_counted_rows() const
{
	return _rows_num;
}


size_t ImageLeapsCounter::reset()
{
	size_t tmp = _leaps_num;
	_leaps_num = 0;
	_rows_num = 0;

	return tmp;
}


size_t ImageLeapsCounter::count_total_leaps(fptr_counter f_counter)
{
	// Rows from top edge.
	for (size_t row_begin_x = width - 1; int(row_begin_x) >= 0; --row_begin_x)
	{
		_leaps_num += _get_row_leaps_data(f_counter, row_begin_x, 0.0).leaps_num;
		++_rows_num;
	}

	// Rows from left edge.
	for (size_t row_begin_y = 0; row_begin_y <= height; ++row_begin_y)
	{
		_leaps_num += _get_row_leaps_data(f_counter, 0.0, row_begin_y).leaps_num;
		++_rows_num;
	}

	// Rows from bottom edge.
	for (size_t row_begin_x = 0; row_begin_x < width; ++row_begin_x)
	{
		_leaps_num += _get_row_leaps_data(f_counter, row_begin_x, height).leaps_num;
		++_rows_num;
	}

	return _leaps_num;
}


ImgHistogram ImageLeapsCounter::count_leaps_to_histogram(fptr_counter f_counter)
{
	ImgHistogram histogram;
	RowData data;

	// Rows from top edge.
	for (size_t row_begin_x = width - 1; int(row_begin_x) >= 0; --row_begin_x)
	{
		data = _get_row_leaps_data(f_counter, row_begin_x, 0.0);
		_leaps_num += data.leaps_num;
		++_rows_num;
		histogram.add_bin(data.leaps_num * 100.0 / data.length);
	}

	// Rows from left edge.
	for (size_t row_begin_y = 0; row_begin_y <= height; ++row_begin_y)
	{
		data = _get_row_leaps_data(f_counter, 0.0, row_begin_y);
		_leaps_num += data.leaps_num;
		++_rows_num;
		histogram.add_bin(data.leaps_num * 100.0 / data.length);
	}

	// Rows from bottom edge.
	for (size_t row_begin_x = 0; row_begin_x < width; ++row_begin_x)
	{
		data = _get_row_leaps_data(f_counter, row_begin_x, height);
		_leaps_num += data.leaps_num;
		++_rows_num;
		histogram.add_bin(data.leaps_num * 100.0 / data.length);
	}

	return std::move(histogram);
}


ImageLeapsCounter::RowData ImageLeapsCounter::_get_row_leaps_data(fptr_counter f_counter, double curr_x, double curr_y) const
{
	double next_x = curr_x + _dx;
	double next_y = curr_y + _dy;

	bool next_intensity;
	bool current_intensity = f_counter(img.get_pixel(curr_x, curr_y));

	size_t leaps = 0;
	size_t len = 0;
	while ((int(curr_x) >= 0)
		   && (int(curr_y) >= 0)
		   && (int(next_x) >= 0)
		   && (int(next_y) >= 0)
		   && (int(curr_x) < int(width))
		   && (int(curr_y) < int(height))
		   && (int(next_x) < int(width))
		   && (int(next_y) < int(height)))
	{
		next_intensity = f_counter(img.get_pixel(next_x, next_y));

		if (current_intensity != next_intensity)
			++leaps;

		curr_x = next_x;
		curr_y = next_y;

		while ((int(curr_x) == int(next_x))
			   && (int(curr_y) == int(next_y)))
		{
			next_x += _dx;
			next_y += _dy;
		}

		current_intensity = next_intensity;
		++len;
	}

	return {leaps, len};
}
