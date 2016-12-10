#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__


#include <iostream>
#include <vector>
#include <memory>


#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>


class Image : public png::image<png::rgb_pixel>
{
	public:
		Image();
		Image(const size_t& width, const size_t& height);
		Image(std::istream& in);
		~Image();

		bool isEmpty() const;
		size_t getWidth() const;
		size_t getHeight() const;

		void load(std::istream& in);
		void save(std::ostream& out);

		Image resize(const size_t& width, const size_t& height);

	private:
		using super = png::image<png::rgb_pixel>;
};


/*
template<class Img>
struct ImageTratis {};


template<>
struct ImageTratis<png::image<png::rgb_pixel>>
{
	using pixel = png::rgb_pixel;
	using image = png::image<png::rgb_pixel>;

	static const size_t pixelDepth = 3;
};


template<class Img, class Traits = ImageTratis<Img>>
class ImageWrap
{
	public:
		Image(std::istream& in);
		~Image();

		Image resize(const size_t& width,
					 const size_t& height);

	private:
		Img _data;
};
*/


#endif // __IMAGE_HPP__
