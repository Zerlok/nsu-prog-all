#ifndef __GUI_LABEL_HPP__
#define __GUI_LABEL_HPP__


#include <string>
#include <sstream>
#include "core/opengls.hpp"
#include "core/gui.hpp"


class GUILabel : public GUIComponent
{
	public:
		// Inner classes.
		enum class Font
		{
			HELVETICA_10,
			HELVETICA_12,
			HELVETICA_18,
			TIMES_10,
			TIMES_24,
		};

		// Constructors / Destructor.
		GUILabel(const std::string& text = "",
				 const size_t& x = 0,
				 const size_t& y = 0,
				 const size_t& width = 1,
				 const size_t& height = 1);
		GUILabel(const GUILabel& comp);
		GUILabel(GUILabel&& comp);
		virtual ~GUILabel();

		// Operators.
		GUILabel& operator=(const GUILabel& comp);
		GUILabel& operator=(GUILabel&& comp);

		GUILabel& operator<<(std::ostream& (*manipulator)(std::ostream&));
		template<class T> GUILabel& operator<<(const T& t)
		{
			_textStream << t;
			return (*this);
		}

		// Methods.
		std::string getText() const;
		const Font& getFont() const;

		GUILabel& toGUILabel();
		const GUILabel& toGUILabel() const;

		void setFont(const Font& font);
		void draw(const size_t& frameWidth,
				  const size_t& frameHeight) const;

	protected:
		// Fields.
		std::stringstream _textStream;
		Font _font;

		// Methods.
		void* _getFontDrawFunction() const;
		void _clearText();
};


#endif // __GUI_LABEL_HPP__
