#include "image.hpp"


#include "grid.hpp"


Image::Image()
	: QImage()
{
}


Image::Image(const size_t& width, const size_t& height)
	: QImage(width, height, QImage::Format_RGB32)
{
}


Image::~Image()
{
}


Image Image::resize(const size_t& width, const size_t& height, const ResizeType& type)
{
	Image resized(width, height);
	resized.clear();

	switch (type)
	{
		case ResizeType::SLOW:
			_slowResize(*this, resized);
			break;

		case ResizeType::FAST:
		default:
			_fastResize(*this, resized);
			break;
	}

	return resized;
}


void Image::clear()
{
	static const QRgb zero = qRgba(0, 0, 0, 0);
	for (int y = 0; y < height(); ++y)
		for (int x = 0; x < width(); ++x)
			setPixel(x, y, zero);
}


void Image::_fastResize(const Image& src, Image& dst)
{
	const Grid srcGrid(src.width(), src.height(), 1, 1);
	Grid dstGrid(dst.width(), dst.height());

	OverlayIterator it = overlay(dstGrid, srcGrid);
	const bool isScaleDown = (dstGrid.getCell().area() > srcGrid.getCell().area());
	Grid::iterator& srcIt = (isScaleDown ? it.getInner() : it.getOutter());
	Grid::iterator& dstIt = (isScaleDown ? it.getOutter() : it.getInner());

	const float wr = dstGrid.getCell().width;
	const float hr = dstGrid.getCell().height;

	for (; !it.isOutterEnd(); ++it)
	{
		for (; !it.isInnerEnd(); ++it)
		{
			const float x = dstIt.getX() / wr;
			const float y = dstIt.getY() / hr;
			dst.setPixel(x, y, src.pixel(srcIt.getX(), srcIt.getY()));
		}
	}
}


void Image::_slowResize(const Image& src, Image& dst)
{
	const Grid srcGrid(src.width(), src.height());
	Grid dstGrid(dst.width(), dst.height());

	OverlayIterator it = overlay(dstGrid, srcGrid);

	Color color;
	const float widthRatio = dstGrid.getCell().width;
	const float heightRatio = dstGrid.getCell().height;
	const float dstPxArea = dstGrid.getCell().area();

	/*
	 * If dst image has more pixels than src image (scale up),
	 * then dst pixels are smaller than src image pixels (meaning that the
	 * images' total areas are the same). By changing image size we do not
	 * change its area, we just change pixels amount.
	 * Otherwise, dst image has less pixels than src image (scale down),
	 * then dst pixels are bigger than src image pixels.
	 */
	if (dstPxArea > srcGrid.getCell().area()) // scale down.
	{
		for (Grid::iterator& out = it.getOutter(); !it.isOutterEnd(); ++it)
		{
			color = Color(0, 0, 0, 0);
			for (Grid::iterator& in = it.getInner(); !it.isInnerEnd(); ++in)
			{
				const Color px = src.pixel(in.getX(), in.getY());
				const float areaRatio = it.getCell().area() / dstPxArea;
				color += px * areaRatio;
			}
			dst.setPixel(out.getX() / widthRatio, out.getY() / heightRatio, color.toQrgb());
		}
	}
	else // scale up.
	{
		for (Grid::iterator& out = it.getOutter(); !it.isOutterEnd(); ++it)
		{
			for (Grid::iterator& in = it.getInner(); !it.isInnerEnd(); ++in)
			{
				const int x = in.getX() / widthRatio;
				const int y = in.getY() / heightRatio;

				if ((x >= dst.width())
						|| (y >= dst.height()))
				{
					std::cerr << "Out of dst range (" << dst.width() << 'x' << dst.height() << "): "
							  << x << ", " << y << " (" << in.getX() << ", " << in.getY() << ')' << std::endl
							  << it.getInnerGrid() << " " << in.getCell() << std::endl
							  << std::endl;
					return;
				}

				const Color px = src.pixel(out.getX(), out.getY());
				const float areaRatio = it.getCell().area() / dstPxArea;
				color = dst.pixel(x, y);
				color += px * areaRatio;
				dst.setPixel(x, y, color.toQrgb());
			}
		}
	}
}
