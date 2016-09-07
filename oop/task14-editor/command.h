#ifndef __COMMAND_H__
#define __COMMAND_H__


#include <string>
#include <vector>
#include <iostream>
#include "factory.h"


using CommandFactory = Factory<std::string, Command>;


class Command
{
	public:
		class Type;

		Command(const Type& type, bool is_modif)
			: _type(type),
			  _is_modifying(is_modif) { }
		virtual ~Command() { }

		const Type& get_type() const { return _type; }
		bool is_modifying() const { return _is_modifying; }

		virtual std::string execute(const std::string& data) = 0;

	protected:
		Type _type;
		bool _is_modifying;
};


class Command::Type
{
	public:
		using Names = std::vector<std::string>;
		using Types = std::vector<Type>;

		static const Names& get_types_names();
		static const Types& get_types();

		static size_t index_of(const std::string& name);
		static size_t index_of(const Type& type);

		static const Type& registrate(const std::string& name);

		static const Type& get(const std::string& name);
		static const Type& get(const size_t& idx);

		Type(const Type& type);
		Type& operator=(const Type& type);
		~Type() {}

		const std::string& get_name() const;
		size_t get_index() const;

		friend std::ostream operator<<(std::ostream& out, const Type& type);
		friend std::istream operator>>(std::istream& in, Type& type);

	private:
		static Names _names;
		static Types _types;
		static Type registrate(const size_t& idx, const std::string& name);

		Type(const std::string& name);

		std::string _name;
};


std::ostream operator<<(std::ostream& out, const Command::Type& type);
std::istream operator>>(std::istream& in, Command::Type& type);


// __COMMAND_H__
#endif
