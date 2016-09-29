#include "logger.hpp"


Logger* Logger::_instance = nullptr;
const std::string Logger::CONSTRUCTOR_MESSAGE = "Logger was created";
const std::string Logger::DESTRUCTOR_MESSAGE = "Logger was stopped";


void Logger::init(std::ostream& out, const Level& level)
{
	static Logger instance(out, level);
}


Logger& Logger::getInstance(std::ostream& out, const Level& level)
{
	init(out, level);
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


std::ostream& Logger::strTimestamp(std::ostream& out)
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


Logger::Logger(std::ostream& output, const Level& level)
	: _output(output),
	  _level(validateInitialLevel(level))
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
		_output << '[' << strTimestamp << "] [" << level << "] ";

		if (funcname != nullptr)
			_output << "@" << funcname << " ";

		if (filename != nullptr)
			_output << "(in file " << filename << ':' << linenum << ") ";
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
		default:
			return out;
	}
}
