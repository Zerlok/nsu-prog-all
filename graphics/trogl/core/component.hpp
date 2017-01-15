#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__


#include <string>
#include <vector>
#include <iostream>
#include <sharedpointer.h>
#include "animation.hpp"


class Component : public Animatable
{
	public:
		// Inner classes.
		enum class Type
		{
			TEXTURE,
			MATERIAL,
			OBJECT,
		};

		class Hash
		{
			public:
				size_t operator()(const Component& c) const;
		};

		// Constructors / Destructor.
		Component(const Type& t,
				  const std::string& name = "");
		Component(const Component& c);
		Component(Component&& c);
		virtual ~Component();

		// Operators.
		Component& operator=(const Component& c);
		Component& operator=(Component&& c);

		bool operator==(const Component& c) const;
		bool operator!=(const Component& c) const;
		bool operator<(const Component& c) const;
		bool operator>(const Component& c) const;

//		Component& operator+=(const Component& c);
//		Component& operator*=(const float& ratio);
//		Component operator+(const Component& c) const;
//		Component operator*(const float& ratio) const;

		// Methods.
		const size_t& getId() const;
		const Type& getType() const;

		Component& toComponent();
		const Component& toComponent() const;

		// Virtual methods.
		virtual std::string toString() const;

		// Friend functions.
		friend std::ostream& operator<<(std::ostream& out, const Component& c);

	private:
		// Static fields.
		static size_t _globID;

		// Fields.
		Type _type;
		size_t _id;
};

using ComponentPtr = SharedPointer<Component, Animatable>;

std::ostream& operator<<(std::ostream& out, const Component& c);


#endif // __COMPONENT_HPP__
