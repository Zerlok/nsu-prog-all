#ifndef __EDITOR_ERRORS_H__
#define __EDITOR_ERRORS_H__


#include <iostream>
#include <string>
#include <vector>


class Error
{
	public:
		struct label
		{
			static const std::string error;
			static const std::string message;
		};

		struct type
		{
			static const std::string an_error;

			static const std::string invalid_argument;
			static const std::string invalid_arguments_num;
			static const std::string invalid_argument_type;

			static const std::string invalid_command_name;
		};

		Error(const std::string& t = type::an_error)
			: errtype(t),
			  message() {}
		Error(const std::string& type, const std::string& msg)
			: errtype(type),
			  message(msg) {}
		Error(const Error&) = default;
		Error(Error&&) = default;

		Error& operator=(const Error&) = default;
		Error& operator=(Error&&) = default;

		// Fields.
		std::string errtype;
		std::string message;
};
using Errors = std::vector<Error>;


std::ostream& operator<<(std::ostream& out, const Error& e);


// __EDITOR_ERRORS_H__
#endif

