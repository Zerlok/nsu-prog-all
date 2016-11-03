#ifndef __GUI_LABEL_HPP__
#define __GUI_LABEL_HPP__


#include <string>
#include <sstream>
#include "core/gui.hpp"


class GUILabel : public GUIComponent
{
	public:
		GUILabel(const std::string& text = "",
				 const size_t& x = 0,
				 const size_t& y = 0,
				 const size_t& width = 1,
				 const size_t& height = 1);
		GUILabel(const GUILabel& comp);
		GUILabel(GUILabel&& comp);
		virtual ~GUILabel();

		GUILabel& operator=(const GUILabel& comp);
		GUILabel& operator=(GUILabel&& comp);

		std::string getText() const;

		GUILabel& operator<<(std::ostream& (*manipulator)(std::ostream&));

		template<class T>
		GUILabel& operator<<(const T& t)
		{
			_textStream << t;
			return (*this);
		}

	protected:
		std::stringstream _textStream;

		void clearText();
};


#endif // __GUI_LABEL_HPP__
