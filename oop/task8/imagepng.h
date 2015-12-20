#ifndef __IMAGEPNG_H__
#define __IMAGEPNG_H__


#include <iostream>
#include <string>
#include <png++/png.hpp>


class GrayPNG : public png::image<png::gray_pixel>
{
	public:
		using pixel = png::gray_pixel;

		GrayPNG(int width, int height);
		~GrayPNG();

	private:
		using super = png::image<pixel>;
};


class ImagePNG : public png::image<png::rgb_pixel>
{
	public:
		using pixel = png::rgb_pixel;

		class iterator;
		class const_iterator;

		ImagePNG(const std::string &filename);
		~ImagePNG();

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();

		GrayPNG grayscale() const;

	private:
		using super = png::image<pixel>;
};


class ImagePNG::iterator
{
	public:
		iterator();
		iterator(int x, int y, ImagePNG *container);
		iterator(const iterator &it);
		iterator(const iterator &&it);
		~iterator();

		bool operator==(const iterator &it) const;
		bool operator!=(const iterator &it) const;

		pixel operator*();

		iterator &operator=(const iterator &it);
		iterator &operator=(const pixel &p);

		iterator &operator++();
		iterator operator++(int);

	private:
		int _num;
		ImagePNG *_container;

		int get_x() const;
		int get_y() const;
};


std::ostream &operator<<(std::ostream &out, const png::gray_pixel);
std::ostream &operator<<(std::ostream &out, const png::rgb_pixel &p);


// __IMAGEPNG_H__
#endif
