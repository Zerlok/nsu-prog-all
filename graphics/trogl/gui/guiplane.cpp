#include "guiplane.hpp"


GUIPlane::GUIPlane(const size_t& x,
				   const size_t& y,
				   const size_t& width,
				   const size_t& height,
				   const Color& fgColor,
				   const Color& bgColor)
	: GUIComponent(GUIComponent::Type::PLANE, x, y, width, height, fgColor, bgColor)
{
}


GUIPlane::~GUIPlane()
{
}

