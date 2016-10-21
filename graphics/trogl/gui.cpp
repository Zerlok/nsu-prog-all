#include "gui.hpp"


#include <logger.hpp>


loggerType loggerInstance = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


GUIComponent::GUIComponent(const Type& type,
						   const size_t& x,
						   const size_t& y,
						   const size_t& width,
						   const size_t& height,
						   const Color& fgColor,
						   const Color& bgColor)
	: _guiComponentType(type),
	  _x(x),
	  _y(y),
	  _width(width),
	  _height(height),
	  _fgColor(fgColor),
	  _bgColor(bgColor)
{
}


GUIComponent::GUIComponent(const GUIComponent& comp)
	: _guiComponentType(comp._guiComponentType),
	  _x(comp._x),
	  _y(comp._y),
	  _width(comp._width),
	  _height(comp._height),
	  _fgColor(comp._fgColor),
	  _bgColor(comp._bgColor)
{
}


GUIComponent::GUIComponent(GUIComponent&& comp)
	: _guiComponentType(std::move(comp._guiComponentType)),
	  _x(std::move(comp._x)),
	  _y(std::move(comp._y)),
	  _width(std::move(comp._width)),
	  _height(std::move(comp._height)),
	  _fgColor(std::move(comp._fgColor)),
	  _bgColor(std::move(comp._bgColor))
{
}


GUIComponent::~GUIComponent()
{
}


GUIComponent& GUIComponent::operator=(const GUIComponent& comp)
{
	_guiComponentType = comp._guiComponentType;
	_x = comp._x;
	_y = comp._y;
	_width = comp._width;
	_height = comp._height;
	_fgColor = comp._fgColor;
	_bgColor = comp._bgColor;

	return (*this);
}


GUIComponent& GUIComponent::operator=(GUIComponent&& comp)
{
	_guiComponentType = std::move(comp._guiComponentType);
	_x = std::move(comp._x);
	_y = std::move(comp._y);
	_width = std::move(comp._width);
	_height = std::move(comp._height);
	_fgColor = std::move(comp._fgColor);
	_bgColor = std::move(comp._bgColor);

	return (*this);
}


const GUIComponent::Type& GUIComponent::getGuiComponentType() const
{
	return _guiComponentType;
}


const size_t& GUIComponent::getX() const
{
	return _x;
}


const size_t& GUIComponent::getY() const
{
	return _y;
}


const size_t& GUIComponent::getWidth() const
{
	return _width;
}


const size_t& GUIComponent::getHeight() const
{
	return _height;
}


const Color& GUIComponent::getFgColor() const
{
	return _fgColor;
}


const Color& GUIComponent::getBgColor() const
{
	return _bgColor;
}


void GUIComponent::setX(const size_t& x)
{
	_x = x;
}


void GUIComponent::setY(const size_t& y)
{
	_y = y;
}


void GUIComponent::setWidth(const size_t& width)
{
	_width = width;
}


void GUIComponent::setHeight(const size_t& height)
{
	_height = height;
}


void GUIComponent::setFgColor(const Color& fgColor)
{
	_fgColor = fgColor;
}


void GUIComponent::setBgColor(const Color& bgColor)
{
	_bgColor = bgColor;
}


// ------------ GUI ------------ //

GUI::GUI()
    : Component(Component::Type::GUI),
      _components()
{
}


GUI::~GUI()
{
}


bool GUI::addComponent(const GUIComponentPtr& gcomp)
{
    if (!gcomp)
		return false;

	_components.push_back(gcomp);
	return true;
}


const GUI::Components& GUI::getComponents() const
{
	return _components;
}
