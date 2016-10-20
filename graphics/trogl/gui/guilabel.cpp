#include "guilabel.hpp"


GUILabel::GUILabel(const std::string& text,
				   const size_t& x,
				   const size_t& y,
				   const size_t& width,
				   const size_t& height)
	: GUIComponent(GUIComponent::Type::LABEL, x, y, width, height),
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


void GUILabel::clearText()
{
	_textStream.str("");
}
