#ifndef __GUI_HPP__
#define __GUI_HPP__


#include <vector>
#include <sstream>
#include "component.hpp"


class GUIComponent
{
	public:
		GUIComponent(const size_t& x,
					 const size_t& y,
					 const size_t& width,
					 const size_t& height);
		GUIComponent(const GUIComponent& comp);
		GUIComponent(GUIComponent&& comp);
		virtual ~GUIComponent();

		GUIComponent& operator=(const GUIComponent& comp);
		GUIComponent& operator=(GUIComponent&& comp);

		const size_t& getX() const;
		const size_t& getY() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;

	protected:
		size_t _x;
		size_t _y;
		size_t _width;
		size_t _height;
};


class GUILabel : public GUIComponent
{
	public:
		GUILabel(const std::string& text,
				 const size_t& x,
				 const size_t& y,
				 const size_t& width,
				 const size_t& height);
		GUILabel(const GUILabel& comp);
		GUILabel(GUILabel&& comp);
		~GUILabel();

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

	private:
		std::stringstream _textStream;
};


class GUI : public Component
{
	public:
		using Components = std::vector<GUIComponent>;

		GUI();
		~GUI();

		void addComponent(const GUIComponent& gcomp);

		const Components& getComponents() const;

	private:
		Components _components;
};


#endif // __GUI_HPP__
