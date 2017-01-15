#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__


#include <iostream>
#include <string>
#include <unordered_map>
#include <sharedpointer.h>


class Component
{
	public:
		// Inner classes.
		using Type = std::string;
		using Types = std::unordered_map<Type, size_t>;

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
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		// Methods.
		bool sameType(const Component& c) const;
		bool sameType(Component&& c) const;

		const Type& getType() const;
		const size_t& getId() const;
		const std::string& getName() const;
		size_t getHash() const;

		void rename(const std::string& name);

		// Virtual methods.
		virtual std::string toString() const;

		// Friend functions.
		friend std::ostream& operator<<(std::ostream& out, const Component& c);

	private:
		// Static fields.
		static size_t _globID;
		static Types _types;
		static std::hash<Type> _typeHash;
		static std::hash<size_t> _idHash;

		// Statuc methods.
		static const size_t& _createIdFor(const Type& type);
		static std::string _nextNumberOf(const std::string& name);
		static std::string _nameWithId(const std::string& name, const size_t& id);
		static void _appendWithNumber(std::string& name);
		static void _renameIfEmptyName(const Type& type, std::string& name);

		// Fields.
		Type _type;
		size_t _id;
		std::string _name;
};

using ComponentPtr = SharedPointer<Component>;

std::ostream& operator<<(std::ostream& out, const Component& c);


#endif // __COMPONENT_HPP__
