#include "logger.hpp"


Logger* Logger::_instance = nullptr;
const std::string Logger::CONSTRUCTOR_MESSAGE = "Logger was started";
const std::string Logger::DESTRUCTOR_MESSAGE = "Logger was stopped";
const char* Logger::EMPTY_STRING = "none";


void Logger::init(std::ostream& out, const Level& level, const Description& descr)
{
	static Logger instance(out, level, descr);
}


Logger& Logger::getInstance(std::ostream& out, const Level& level, const Logger::Description& descr)
{
	init(out, level, descr);
	return (*_instance);
}


Logger& Logger::out(const Logger::Level& level,
					const char* funcname,
					const char* filename,
					const int& linenum)
{
	return _instance->_out(level, funcname, filename, linenum);
}


Logger& Logger::debug(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _instance->_debug(funcname, filename, linenum);
}


Logger& Logger::info(const char* funcname,
					 const char* filename,
					 const int& linenum)
{
	return _instance->_info(funcname, filename, linenum);
}


Logger& Logger::warning(const char* funcname,
						const char* filename,
						const int& linenum)
{
	return _instance->_warning(funcname, filename, linenum);
}


Logger& Logger::error(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _instance->_error(funcname, filename, linenum);
}


Logger& Logger::fatal(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _instance->_fatal(funcname, filename, linenum);
}


Logger& Logger::end()
{
	return _instance->_end();
}


std::ostream& Logger::addTimestamp(std::ostream& out)
{
	static struct timeval time;
	gettimeofday(&time, NULL);
	return out << time.tv_sec << '.' << time.tv_usec;
}


Logger::Level Logger::validateInitialLevel(const Logger::Level& level)
{
	switch (level)
	{
		case Level::DEBUG:
		case Level::INFO:
		case Level::WARNING:
		case Level::ERROR:
			return level;

		case Level::NONE:
		default:
			return Level::DEBUG;
	}
}


Logger::Logger(std::ostream& output, const Level& level, const Description& descr)
	: _output(output),
	  _level(validateInitialLevel(level)),
	  _description(descr)
{
	_instance = this;
	info() << CONSTRUCTOR_MESSAGE << end;
}


Logger::~Logger()
{
	info() << DESTRUCTOR_MESSAGE << end;
}


Logger& Logger::_out(const Level& level,
					const char* funcname,
					const char* filename,
					const int &linenum)
{
	if (_current_message_level != Level::NONE)
		return (*this);

	_current_message_level = level;
	if (validateCurrentLevel())
	{
		_output << '[' << addTimestamp << "] ";

		switch (_description)
		{
			case Description::LEVEL:
				_output << '[' << level << "] ";
				break;
			case Description::LEVEL_AND_FUNCTION:
				_output << '[' << level
						<< "] @" << funcname << ' ';
				break;
			case Description::FULL:
				_output << '[' << level
						<< "] @" << funcname
						<< " (in file " << filename << ':' << linenum << ") ";
				break;
			case Description::MESSAGE_ONLY:
			default:
				break;
		}
	}

	return (*this);
}


Logger& Logger::_debug(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _out(Level::DEBUG, funcname, filename, linenum);
}


Logger& Logger::_info(const char* funcname,
					 const char* filename,
					 const int& linenum)
{
	return _out(Level::INFO, funcname, filename, linenum);
}


Logger& Logger::_warning(const char* funcname,
						const char* filename,
						const int& linenum)
{
	return _out(Level::WARNING, funcname, filename, linenum);
}


Logger& Logger::_error(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _out(Level::ERROR, funcname, filename, linenum);
}


Logger& Logger::_fatal(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return _out(Level::FATAL, funcname, filename, linenum);
}


Logger& Logger::_end()
{
	if (validateCurrentLevel())
		_output << std::endl;

	_current_message_level = Level::NONE;
	return (*this);
}


Logger& Logger::operator<<(Logger& (*manipulator)(void))
{
	return manipulator();
}


Logger& Logger::operator<<(std::ostream&(*manipulator)(std::ostream&))
{
	if (validateCurrentLevel())
		manipulator(_output);

	return (*this);
}


bool Logger::validateCurrentLevel() const
{
	return (int(_current_message_level) >= int(_level));
}


std::ostream&operator<<(std::ostream& out, const Logger::Level& level)
{
	switch (level)
	{
		case Logger::Level::DEBUG:
			return out << "DEBUG";
		case Logger::Level::INFO:
			return out << "INFO";
		case Logger::Level::WARNING:
			return out << "WARNING";
		case Logger::Level::ERROR:
			return out << "ERROR";
		case Logger::Level::FATAL:
			return out << "FATAL";
		default:
			return out;
	}
}
