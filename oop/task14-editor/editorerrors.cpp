#include "editorerrors.h"


const std::string Error::label::error = "# ERROR: ";
const std::string Error::label::message = "# ERROR MESSAGE: ";

const std::string Error::type::an_error = "An error!";
const std::string Error::type::invalid_argument = "Invalid argument!";
const std::string Error::type::invalid_arguments_num = "Invalid number of arguments!";
const std::string Error::type::invalid_argument_type = "Invalid type of the argument!";
const std::string Error::type::invalid_command_name = "Invalid command name!";


std::ostream& operator<<(std::ostream& out, const Error& e)
{
	out << Error::label::error << e.errtype;
	if (!e.message.empty())
	{
		out << std::endl;
		out << Error::label::message << e.message;
	}

	return out;
}
