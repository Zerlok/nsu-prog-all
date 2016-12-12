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
	const float dstPxArea = dstGrid.getCell().area();

	if (dstPxArea > srcGrid.getCell().area())
	{
		for (Grid::iterator& out = it.getOutter(); out != it.getOutterEnd(); ++it)
		{
			color = 0;
			for (Grid::iterator& in = it.getInner(); in != it.getInnerEnd(); ++it)
			{
				const QRgb px = src.pixel(in.getX(), in.getY());
				const float pxArea = it.getCell().area();
				color +=  px * pxArea / dstPxArea;
			}
			dst.setPixel(out.getX(), out.getY(), color);
		}
	}
	else
	{
		for (Grid::iterator& out = it.getOutter(); out != it.getOutterEnd(); ++it)
		{
			for (Grid::iterator& in = it.getInner(); in != it.getInnerEnd(); ++it)
			{
				const QRgb px = src.pixel(out.getX(), out.getY());
				const float pxArea = it.getCell().area();
				color = dst.pixel(in.getX(), in.getY());
				color += px * pxArea / dstPxArea;
				dst.setPixel(in.getX(), in.getY(), color);
			}
		}
	}
}
