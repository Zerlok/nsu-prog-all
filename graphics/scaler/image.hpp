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

		struct Color
		{
			Color(const int& r = 0,
				  const int& g = 0,
				  const int& b = 0,
				  const int& a = 0)
				: red(r),
				  green(g),
				  blue(b),
				  alpha(a) {}
			Color(const QRgb& rgb)
				: red(qRed(rgb)),
				  green(qGreen(rgb)),
				  blue(qBlue(rgb)),
				  alpha(qAlpha(rgb)) {}
			~Color() {}

			QRgb toQrgb() const
			{
				return qRgba(red, green, blue, alpha);
			}

			Color& operator=(const Color& c)
			{
				red = c.red;
				green = c.green;
				blue = c.blue;
				alpha = c.alpha;

				return (*this);
			}
			Color& operator=(const QRgb& rgb)
			{
				red = qRed(rgb);
				green = qGreen(rgb);
				blue = qBlue(rgb);
				alpha = qAlpha(rgb);

				return (*this);
			}
			Color& operator+=(const Color& c)
			{
				red += c.red;
				green += c.green;
				blue += c.blue;
				alpha += c.alpha;

				return (*this);
			}
			Color operator*(const float& val) const
			{
				Color c;
				c.red = red * val;
				c.green = green * val;
				c.blue = blue * val;
				c.alpha = alpha * val;

				return c;
			}

			int red;
			int green;
			int blue;
			int alpha;
		};

		Image();
		Image(const size_t& width, const size_t& height);
		~Image();

		Image resize(const size_t& width, const size_t& height, const ResizeType& type = ResizeType::SLOW);
		void clear();

	private:
		static void _fastResize(const Image& src, Image& dst);
		static void _slowResize(const Image& src, Image& dst);
};


#endif // __IMAGE_HPP__
