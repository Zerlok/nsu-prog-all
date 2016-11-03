#ifndef __GUI_PLANE_HPP__
#define __GUI_PLANE_HPP__


#include "core/gui.hpp"


class GUIPlane : public GUIComponent
{
	public:
		GUIPlane(const size_t& x = 0,
				 const size_t& y = 0,
				 const size_t& width = 1,
				 const size_t& height = 1,
				 const Color& fgColor = Color::white,
				 const Color& bgColor = Color::black);
		virtual ~GUIPlane();
};


#endif // __GUI_PLANE_HPP__
