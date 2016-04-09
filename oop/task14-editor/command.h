#ifndef __COMMAND_H__
#define __COMMAND_H__


#include <iostream>
#include <string>
#include <vector>
#include "factory.h"
#include "history.h"
#include "editorerrors.h"


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


using CommandsPrototypes = PrototypeFactory<std::string, Command>;


class Command::AbstractPrototype
{
	public:
		struct Result
		{
			// Constructors / Destructor.
			Result(Command* p = nullptr, const Errors& e = Errors())
				: ptr(p), errors(e) {}
			Result(const Result&) = default;
			Result(Result&&) = default;

			// Operators.
			Result& operator=(const Result&) = default;
			Result& operator=(Result&&) = default;

			bool is_valid() const { return errors.empty(); }
			operator bool() const { return is_valid(); }
			bool operator!() const { return !(this->operator bool()); }

			Command *ptr = nullptr;
			Errors errors;
		};

		AbstractPrototype()
			: arguments() {}
		AbstractPrototype(const Strings& args)
			: arguments(args) {}
		virtual ~AbstractPrototype() = default;
		virtual Result construct() const = 0;

		void set_arguments(const Strings& args)
		{
			arguments = args;
		}

	protected:
		Strings arguments;
};


// __COMMAND_H__
#endif
