#ifndef __GUI_HPP__
#define __GUI_HPP__


#include <vector>
#include <sharedpointer.h>
#include "core/opengls.hpp"
#include "common/color.hpp"
#include "component.hpp"


class GUIComponent
{
	public:
		// Inner classes.
		enum class Type
		{
			LABEL = 0,
			PLANE,
		};

		// Constructors / Destructor.s
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

		// Operators.
		GUIComponent& operator=(const GUIComponent& comp);
		GUIComponent& operator=(GUIComponent&& comp);

		// Methods.
		const Type& getGuiComponentType() const;
		const size_t& getX() const;
		const size_t& getY() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		const Color& getFgColor() const;
		const Color& getBgColor() const;

		GUIComponent& toGUIComponent();
		const GUIComponent& toGUIComponent() const;

		void setX(const size_t& x);
		void setY(const size_t& y);
		void setWidth(const size_t& width);
		void setHeight(const size_t& height);
		void setFgColor(const Color& fgColor);
		void setBgColor(const Color& bgColor);

		// Virtual methods.
		virtual void draw(const size_t&, const size_t&) const = 0;

	private:
		// Fields.
		Type _guiComponentType;

	protected:
		// Fields.
		size_t _x;
		size_t _y;
		size_t _width;
		size_t _height;

		Color _fgColor;
		Color _bgColor;

		// Methods.
		GLfloat _countXPos(const size_t& frameWidth) const;
		GLfloat _countYPos(const size_t& frameHeight) const;
};

using GUIComponentPtr = SharedPointer<GUIComponent>;


class GUI : public Component
{
	public:
		// Inner classes.
		using Components = std::vector<GUIComponentPtr>;

		// Constructors / Destructor.
		GUI();
		virtual ~GUI();

		// Methods.
		bool addComponent(const GUIComponentPtr& gcomp);

		const Components& getComponents() const;

	protected:
		// Fields.
		Components _components;
};

using GUIPtr = SharedPointer<GUI>;


#endif // __GUI_HPP__
