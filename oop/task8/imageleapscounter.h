#ifndef __IMAGELEAPSCOUNTER_H__
#define __IMAGELEAPSCOUNTER_H__


#include "imagepng.h"
#include "histogram.h"
#include "utils.h"


class ImageLeapsCounter
{
	public:
		typedef	bool fptr_counter(const ImagePNG::pixel_t &pixel);

		typedef struct RowDataStruct
		{
			size_t leaps_num;
			size_t length;
		} RowData;

		ImageLeapsCounter(const ImagePNG &img);
		~ImageLeapsCounter();

		size_t get_counted_leaps() const;
		size_t get_counted_rows() const;

		size_t count_total_leaps(fptr_counter f_counter);
		ImgHistogram count_leaps_to_histogram(fptr_counter f_counter);

		void set_direction(const int degrees);
		size_t reset();

	private:
		// Defaults.
		static const double _default_dx;
		static const double _default_dy;

		// Image info.
		const ImagePNG &img;
		const double width;
		const double height;

		// Row direction.
		double _dx;
		double _dy;

		// Counter.
		size_t _leaps_num;
		size_t _rows_num;

		// Methods.
		RowData _get_row_leaps_data(fptr_counter fptr_counter, double curr_x, double curr_y) const;
};


// __IMAGELEAPSCOUNTER_H__
#endif
