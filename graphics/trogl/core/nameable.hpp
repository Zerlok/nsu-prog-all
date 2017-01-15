#ifndef __NAMEABLE_HPP__
#define __NAMEABLE_HPP__


#include <iostream>
#include <string>


class Nameable
{
	public:
		Nameable(const std::string& name = "");
		Nameable(const Nameable& n);
		Nameable(Nameable&& n);
		virtual ~Nameable();

		Nameable& operator=(const Nameable& n);
		Nameable& operator=(Nameable&& n);

		const std::string& getName() const;
		void rename(const std::string& name);
		void renameWithId(const std::string& name, const size_t& id);

	private:
		std::string _name;

		static std::string _nextNumberOf(const std::string& name);
		static std::string _nameWithId(const std::string& name, const size_t& id);
		static void _appendWithNumber(std::string& name);
		static void _renameIfEmptyName(std::string& name);
};


std::ostream& operator<<(std::ostream& out, const Nameable& n);


#endif // __NAMEABLE_HPP__
