#include "guilabel.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


GUILabel::GUILabel(const std::string& text,
				   const size_t& x,
				   const size_t& y,
				   const size_t& width,
				   const size_t& height)
	: GUIComponent(GUIComponent::Type::LABEL, x, y, width, height),
	  _textStream(),
	  _font(Font::HELVETICA_12)
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
	comp._clearText();
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
	comp._clearText();

	return (*this);
}


std::string GUILabel::getText() const
{
	return std::move(_textStream.str());
}


const GUILabel::Font&GUILabel::getFont() const
{
	return _font;
}


GUILabel& GUILabel::toGUILabel()
{
	return (*this);
}


const GUILabel& GUILabel::toGUILabel() const
{
	return (*this);
}


void GUILabel::setFont(const GUILabel::Font& font)
{
	_font = font;
}


void GUILabel::draw(const size_t& frameWidth,
					const size_t& frameHeight) const
{
	glRasterPos2f(_countXPos(frameWidth), _countYPos(frameHeight));
	glColor4f(_fgColor.getRedF(),
			  _fgColor.getGreenF(),
			  _fgColor.getBlueF(),
			  _fgColor.getAlphaF());

	const char* p = getText().c_str();
	do
		glutBitmapCharacter(_getFontDrawFunction(), *p);
	while (*(++p));
}


void* GUILabel::_getFontDrawFunction() const
{
	switch (_font)
	{
		case Font::HELVETICA_10:
			return GLUT_BITMAP_HELVETICA_10;
		case Font::HELVETICA_12:
			return GLUT_BITMAP_HELVETICA_12;
		case Font::HELVETICA_18:
			return GLUT_BITMAP_HELVETICA_18;
		case Font::TIMES_10:
			return GLUT_BITMAP_TIMES_ROMAN_10;
		case Font::TIMES_24:
			return GLUT_BITMAP_TIMES_ROMAN_24;
	}

	return nullptr;
}


void GUILabel::_clearText()
{
	_textStream.str("");
}
