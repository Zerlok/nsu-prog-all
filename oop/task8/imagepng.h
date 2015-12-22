#ifndef __IMAGEPNG_H__
#define __IMAGEPNG_H__


#include <iostream>
#include <string>
#include <png++/png.hpp>


class ImagePNG : public png::image<png::rgb_pixel>
{
	public:
		using pixel = png::rgb_pixel;

		class iterator;
		class const_iterator;

		ImagePNG(const std::string &filename);
		ImagePNG(int width, int height);
//		ImagePNG(const ImagePNG &img);
		ImagePNG(const ImagePNG &&img);
		~ImagePNG();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

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

		iterator &operator--();
		iterator operator--(int);

		int get_x() const;
		int get_y() const;
		size_t get_num() const;

	private:
		size_t _num;
		ImagePNG *_container;
};
class ImagePNG::const_iterator
{
	public:
		const_iterator();
		const_iterator(int x, int y, const ImagePNG *container);
		const_iterator(const const_iterator &it);
		const_iterator(const const_iterator &&it);
		~const_iterator();

		bool operator==(const const_iterator &it) const;
		bool operator!=(const const_iterator &it) const;

		const pixel operator*() const;

		const_iterator &operator=(const const_iterator &it);

		const_iterator &operator++();
		const_iterator operator++(int);

		const_iterator &operator--();
		const_iterator operator--(int);

		int get_x() const;
		int get_y() const;
		size_t get_num() const;

	private:
		size_t _num;
		const ImagePNG *_container;
};


std::ostream &operator<<(std::ostream &out, const png::gray_pixel);
std::ostream &operator<<(std::ostream &out, const png::rgb_pixel &p);
std::ostream &operator<<(std::ostream &out, const ImagePNG::iterator &it);
std::ostream &operator<<(std::ostream &out, const ImagePNG::const_iterator &it);


// __IMAGEPNG_H__
#endif
