#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__


#include <string>
#include <iostream>


class Component
{
	public:
		enum Type
		{
			GUI,
			SCENE,
			OBJECT,
			MATERIAL,
			TEXTURE,
		};

		Component(const Type& t,
				  const std::string& name = std::string());
		Component(const Component& c);
		Component(Component&& c);
		virtual ~Component();

		Component& operator=(const Component& c);
		Component& operator=(Component&& c);

		bool operator==(const Component& c) const;
		bool operator!=(const Component& c) const;

		const Type& getType() const;

		const std::string& getName() const;
		void setName(const std::string& name);

		virtual Component copy() const;

		friend std::ostream& operator<<(std::ostream& out, const Component& c);

	private:
		static size_t globID;
		Type _type;
		size_t _ID;

		static std::string generateNameFromType(const Type& type, const size_t& id);
		static std::string generateNameFromCopy(const Component& c);

	protected:
		std::string _name;
};

std::ostream& operator<<(std::ostream& out, const Component& c);


#endif // __COMPONENT_HPP__
