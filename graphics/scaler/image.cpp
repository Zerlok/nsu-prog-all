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


void Image::_fastResize(const Image& src, Image& dst)
{
	const float wr = float(src.width()) / float(dst.width());
	const float hr = float(src.height()) / float(dst.height());

	for (int v = 0; v < dst.height(); ++v)
		for (int u = 0; u < dst.width(); ++u)
			dst.setPixel(u, v, src.pixel(u * wr, v * hr));
}


void Image::_slowResize(const Image& src, Image& dst)
{
	const Grid srcGrid(src.width(), src.height());
	Grid dstGrid(dst.width(), dst.height());

	QRgb color;
	OverlayIterator it = overlay(dstGrid, srcGrid);
	const float widthRatio = dstGrid.getCell().width;
	const float heightRatio = dstGrid.getCell().height;
	const float dstPxArea = dstGrid.getCell().area();

	/*
	 * If dst image has more pixels than src image (scale up),
	 * then dst pixels are smaller than src image pixels (meaning that the
	 * images' total areas are the same).
	 * Otherwise, dst image has less pixels than src image (scale down),
	 * then dst pixels are bigger than src image pixels.
	 */
	if (dstPxArea > srcGrid.getCell().area()) // scale up.
	{
		for (Grid::iterator& out = it.getOutter(); it.isOutterEnd(); ++it)
		{
			color = 0;
			for (Grid::iterator& in = it.getInner(); it.isInnerEnd(); ++it)
			{
				const QRgb px = src.pixel(in.getX(), in.getY());
				const float pxArea = it.getCell().area();
				color +=  px * pxArea / dstPxArea;
			}
			dst.setPixel(out.getX() / widthRatio, out.getY() / heightRatio, color);
		}
	}
	else // scale down.
	{
		for (Grid::iterator& out = it.getOutter(); it.isOutterEnd(); ++it)
		{
			for (Grid::iterator& in = it.getInner(); it.isInnerEnd(); ++it)
			{
				const QRgb px = src.pixel(out.getX(), out.getY());
				const float pxArea = it.getCell().area();
				color = dst.pixel(in.getX() / widthRatio, in.getY() / heightRatio);
				color += px * pxArea / dstPxArea;
				dst.setPixel(in.getX() / widthRatio, in.getY() / heightRatio, color);
			}
		}
	}
}
