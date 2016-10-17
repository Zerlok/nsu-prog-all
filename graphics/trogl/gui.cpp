#include "gui.hpp"


GUIComponent::GUIComponent(const size_t& x,
						   const size_t& y,
						   const size_t& width,
						   const size_t& height)
	: _x(x),
	  _y(y),
	  _width(width),
	  _height(height)
{
}


GUIComponent::GUIComponent(const GUIComponent& comp)
	: _x(comp._x),
	  _y(comp._y),
	  _width(comp._width),
	  _height(comp._height)
{
}


GUIComponent::GUIComponent(GUIComponent&& comp)
	: _x(std::move(comp._x)),
	  _y(std::move(comp._y)),
	  _width(std::move(comp._width)),
	  _height(std::move(comp._height))
{
}


GUIComponent::~GUIComponent()
{
}


GUIComponent& GUIComponent::operator=(const GUIComponent& comp)
{
	_x = comp._x;
	_y = comp._y;
	_width = comp._width;
	_height = comp._height;

	return (*this);
}


GUIComponent& GUIComponent::operator=(GUIComponent&& comp)
{
	_x = std::move(comp._x);
	_y = std::move(comp._y);
	_width = std::move(comp._width);
	_height = std::move(comp._height);

	return (*this);
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


GUILabel::GUILabel(const std::string& text,
				   const size_t& x,
				   const size_t& y,
				   const size_t& width,
				   const size_t& height)
	: GUIComponent(x, y, width, height),
	  _textStream()
{
	_textStream.str(text);
}


GUILabel::GUILabel(const GUILabel& comp)
	: GUIComponent(comp),
	  _textStream()
{
	_textStream.str(comp._textStream.str());
}


GUILabel::GUILabel(GUILabel&& comp)
	: GUIComponent(comp),
	  _textStream(std::move(comp._textStream))
{
}


GUILabel::~GUILabel()
{
}


GUILabel& GUILabel::operator=(const GUILabel& comp)
{
	GUIComponent::operator=(comp);
	_textStream.str(comp._textStream.str());

	return (*this);
}


GUILabel& GUILabel::operator=(GUILabel&& comp)
{
	GUIComponent::operator=(comp);
	_textStream = std::move(comp._textStream);

	return (*this);
}


std::string GUILabel::getText() const
{
	return std::move(_textStream.str());
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


void GUI::addComponent(const GUIComponent& gcomp)
{
	_components.push_back(gcomp);
}


const GUI::Components& GUI::getComponents() const
{
	return _components;
}
