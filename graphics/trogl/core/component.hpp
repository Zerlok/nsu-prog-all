#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__


#include <string>
#include <iostream>
#include <sharedpointer.h>


class Component
{
	public:
		// Inner classes.
		enum class Type
		{
			OBJECT,
			SHADER,
			MATERIAL,
			TEXTURE,
			SCENE,
			GUI,
			FRAME,
		};

		class Hash
		{
			public:
				size_t operator()(const Component& c) const;
		};

		// Constructors / Destructor.
		Component(const Type& t,
				  const std::string& name = std::string());
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

		// Methods.
		const size_t& getId() const;
		const Type& getType() const;
		const std::string& getName() const;

		Component& toComponent();
		const Component& toComponent() const;

		void setName(const std::string& name);

		// Virtual methods.
		virtual std::string toString() const;

		// Friend functions.
		friend std::ostream& operator<<(std::ostream& out, const Component& c);

	private:
		// Static fields.
		static size_t _globID;
		static size_t _objectID;
		static size_t _shaderID;
		static size_t _materialID;
		static size_t _textureID;
		static size_t _sceneID;
		static size_t _guiID;
		static size_t _frameID;

		// Static methods.
		static size_t _getTypeId(const Component& type);
		static void _incrementTypeId(const Component& type);
		static void _applyNameFromType(Component& c);
		static void _applyNameFromCopy(Component& c);

		// Fields.
		Type _type;
		size_t _id;
		std::string _name;
};

using ComponentPtr = SharedPointer<Component>;

std::ostream& operator<<(std::ostream& out, const Component& c);


#endif // __COMPONENT_HPP__
