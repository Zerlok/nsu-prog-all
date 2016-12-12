#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__


#include <iostream>
#include <vector>
#include <memory>

#include <QImage>


class Image : public QImage
{
	public:
		enum class ResizeType
		{
			FAST,
			SLOW,
		};

		Image();
		Image(const size_t& width, const size_t& height);
		~Image();

		Image resize(const size_t& width, const size_t& height, const ResizeType& type = ResizeType::SLOW);

	private:
		static void _fastResize(const Image& src, Image& dst);
		static void _slowResize(const Image& src, Image& dst);
};


#endif // __IMAGE_HPP__
