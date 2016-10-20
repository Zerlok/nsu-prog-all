#ifndef __GUI_HPP__
#define __GUI_HPP__


#include <vector>
#include <sharedpointer.h>

#include "common/color.hpp"
#include "component.hpp"


class GUIComponent
{
	public:
		enum class Type
		{
			LABEL = 0,
			PLANE,
		};

		GUIComponent(const Type& type,
					 const size_t& x = 0,
					 const size_t& y = 0,
					 const size_t& width = 1,
					 const size_t& height = 1,
					 const Color& fgColor = Color::white,
					 const Color& bgColor = Color::black);
		GUIComponent(const GUIComponent& comp);
		GUIComponent(GUIComponent&& comp);
		virtual ~GUIComponent();

		GUIComponent& operator=(const GUIComponent& comp);
		GUIComponent& operator=(GUIComponent&& comp);

		const Type& getGuiComponentType() const;
		const size_t& getX() const;
		const size_t& getY() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		const Color& getFgColor() const;
		const Color& getBgColor() const;

		void setX(const size_t& x);
		void setY(const size_t& y);
		void setWidth(const size_t& width);
		void setHeight(const size_t& height);
		void setFgColor(const Color& fgColor);
		void setBgColor(const Color& bgColor);

	private:
		Type _guiComponentType;

	protected:
		size_t _x;
		size_t _y;
		size_t _width;
		size_t _height;

		Color _fgColor;
		Color _bgColor;
};

using GUIComponentPtr = SharedPointer<GUIComponent>;


class GUI : public Component
{
	public:
		using Components = std::vector<GUIComponentPtr>;

		GUI();
		virtual ~GUI();

		bool addComponent(const GUIComponentPtr& gcomp);

		const Components& getComponents() const;

	protected:
		Components _components;
};

using GUIPtr = SharedPointer<GUI>;


#endif // __GUI_HPP__
