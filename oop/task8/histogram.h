#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__


#include <vector>
#include <stdexcept>


static const std::string EMPTY_HISTOGRAM_ERR = "Histogram is empty!";


template<class BinHeight=size_t, class BinWidth=int, class BinPosition=int>
class Histogram
{
	public:
		using height_t = BinHeight;
		using width_t = BinWidth;
		using position_t = BinPosition;

		class Bin
		{
			public:
				Bin(const height_t &h = 0, const width_t &w = 1, const position_t &p = 0)
					: height(h),
					  width(w),
					  pos(p) {}

				Bin(const Bin &b)
					: height(b.height),
					  width(b.width),
					  pos(b.pos) {}

				Bin(const Bin &&b)
					: height(std::move(b.height)),
					  width(std::move(b.width)),
					  pos(std::move(b.pos)) {}

				~Bin() {}

				Bin &operator++()
				{
					++height;

					return (*this);
				}

				Bin operator++(int)
				{
					Bin tmp(*this);
					++height;

					return tmp;
				}

				Bin &operator--()
				{
					--height;

					return (*this);
				}

				Bin operator--(int)
				{
					Bin tmp(*this);
					--height;

					return tmp;
				}

				height_t height;
				width_t width;
				position_t pos;
		};

		using bins_vector_t = std::vector<Bin>;

		// Constructors / Destructor.
		Histogram(const size_t bins_num = 0, const width_t bins_width = 1)
			: _bins_width(bins_width),
			  _bins(bins_num, Bin(0, bins_width))
		{
			for (size_t i = 0; i < bins_num; ++i)
				_bins[i].pos = _count_bin_position(i);
		}

		Histogram(const Histogram &histogram)
			: _bins_width(histogram._bins_width),
			  _bins(histogram._bins)
		{
		}

		Histogram(const Histogram &&histogram)
			: _bins_width(std::move(histogram._bins_width)),
			  _bins(std::move(histogram._bins))
		{
		}

		virtual ~Histogram()
		{
		}

		// Setters.
		void add_bin(const Bin &bin)
		{
			_bins.push_back(bin);
			_bins.back().pos = _count_bin_position(_bins.size() - 1);
		}

		void add_bin(const height_t bin_height = 0, const width_t bin_width = 0)
		{
			add_bin((bin_width > 0)
					? Bin(bin_height, bin_width)
					: Bin(bin_height, _bins_width));
		}

		// Getters.
		size_t size() const
		{
			return _bins.size() * _bins_width;
		}

		typename
		bins_vector_t::iterator begin()
		{
			return _bins.begin();
		}

		typename
		bins_vector_t::iterator end()
		{
			return _bins.end();
		}

		typename
		bins_vector_t::const_iterator begin() const
		{
			return _bins.cbegin();
		}

		typename
		bins_vector_t::const_iterator end() const
		{
			return _bins.cend();
		}

		typename
		bins_vector_t::const_iterator cbegin() const
		{
			return _bins.begin();
		}

		typename
		bins_vector_t::const_iterator cend() const
		{
			return _bins.cend();
		}

		const width_t get_bins_width() const
		{
			return _bins_width;
		}

		const Bin &get_max_bin() const
		{
			if (_bins.empty())
				throw std::invalid_argument(EMPTY_HISTOGRAM_ERR);

			size_t max_indx = 0;
			size_t bins_num = _bins.size();
			for (size_t i = 1; i < bins_num - 1; ++i)
				if (_bins[i].height > _bins[max_indx].height)
					max_indx = i;

			return _bins[max_indx];
		}

		const Bin &get_min_bin() const
		{
			if (_bins.empty())
				throw std::invalid_argument(EMPTY_HISTOGRAM_ERR);

			size_t min_indx = 0;
			for (size_t i = 1; i < _bins.size() - 1; ++i)
				if (_bins[i].height < _bins[min_indx].height)
					min_indx = i;

			return _bins[min_indx];
		}

		Histogram differentiate() const
		{
			Histogram diff_histogram = Histogram(_bins.size() - 1, _bins_width);

			for (size_t i = 0; i < _bins.size() - 1; ++i)
				diff_histogram._bins[i].height = _bins[i].height - _bins[i + 1].height;

			return std::move(diff_histogram);
		}

		Histogram in_percents() const
		{
			Histogram percent_histogram(_bins.size(), _bins_width);
			const height_t offset = get_min_bin().height;
			const height_t highest = get_max_bin().height + offset;

			for (size_t i = 0; i < _bins.size(); ++i)
				percent_histogram._bins[i].height = (_bins[i].height + offset) * 100.0 / highest;

			return std::move(percent_histogram);
		}

		// Operators.
		Histogram &operator=(const Histogram &histogram)
		{
			_bins_width = histogram._bins_width;
			_bins = histogram._bins;

			return (*this);
		}

		Bin &operator[](const size_t &index)
		{
			return _bins[index];
		}

		const Bin &operator[](const size_t &index) const
		{
			return _bins[index];
		}

	private:
		// Fields.
		width_t _bins_width;
		std::vector<Bin> _bins;

		// Methods.
		position_t _count_bin_position(const size_t &index) const
		{
			return (index * _bins_width);
		}

		size_t _count_bin_index(const position_t &position) const
		{
			return (position / _bins_width);
		}
};


// __HISTOGRAM_H__
#endif
