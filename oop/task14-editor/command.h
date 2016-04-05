#ifndef __COMMAND_H__
#define __COMMAND_H__


#include <iostream>
#include <string>
#include <vector>
#include "factory.h"
#include "history.h"


class Command;
using CommandFactory = Factory<std::string, Command>;


class Command
{
	public:
		// Commands types.
		enum class Type
		{
			data_manipulation = 0,
			history_manipulation,
			help,
		};

		// Inner classes.
		class AbstractPrototype;

		struct Error
		{
			Error(const std::string& err, const std::string& msg = "")
				: error(err),
				  message(msg) {}
			Error(const Error&) = default;
			Error(Error&&) = default;

			std::string error;
			std::string message;
		};
		using Errors = std::vector<Error>;
		struct Result
		{
			// Constructors / Destructor.
			Result(const std::string& s = "", const Errors& e = Errors())
				: data(s), errors(e) {}
			Result(const Result&) = default;
			Result(Result&&) = default;

			// Operators.
			Result& operator=(const Result&) = default;
			Result& operator=(Result&&) = default;

			bool is_valid() const { return errors.empty(); }
			operator bool() const { return is_valid(); }
			bool operator!() const { return !(this->operator bool()); }

			// Fields.
			std::string data;
			Errors errors;
		};

		// Typedefs.

		// Constructors / Destructor.
		Command(const Type& type)
			: _type(type) {}
		Command(const Command&) = default;
		Command(Command&&) = default;
		virtual ~Command() {}

		// Operators.
		Command& operator=(const Command&) = default;
		Command& operator=(Command&&) = default;

		// Getters.
		const Type& get_type() const { return _type; }

		// Virtual methods.
		// For data manipulation commands.
		virtual Errors validate(const std::string&, const std::string&) const { return std::move(Errors()); }
		virtual Result execute(const std::string&, std::string&) { return std::move(Result()); }

		// For history manipulation commands.
		virtual Errors validate(const History&) const { return std::move(Errors()); }
		virtual Result execute(History&) { return std::move(Result()); }

	protected:
		Type _type;
};


class Command::AbstractPrototype
{
	public:
		AbstractPrototype(const Type& type, const size_t n)
			: _type(type),
			  _argn(n) {}
		virtual ~AbstractPrototype() {}

		virtual Command* construct(const Strings& args) = 0;

	protected:
		Type _type;
		size_t _argn;
};


inline std::ostream& operator<<(std::ostream& out, const Command::Error& e)
{
	out << "# COMMAND ERROR: " << e.error << std::endl;
	if (!e.message.empty())
		out << "# ERROR MESSAGE: " << e.message << std::endl;

	return out;
}


// __COMMAND_H__
#endif
