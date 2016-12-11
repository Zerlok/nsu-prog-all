#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__


#include <iostream>
#include <vector>
#include <memory>

#include <QImage>


class Image : public QImage
{
	public:
		Image();
		Image(const size_t& width, const size_t& height);
		~Image();

		Image resize(const size_t& width, const size_t& height);
};


#endif // __IMAGE_HPP__
