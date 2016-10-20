#include "logger.hpp"


#include <sys/time.h>


Logger* Logger::_instance = nullptr;
const char* Logger::CONSTRUCTOR_MESSAGE = "========== LOGGER STARTED ==========";
const char* Logger::DESTRUCTOR_MESSAGE = "========== LOGGER STOPPED ==========";
const char* Logger::EMPTY_STRING = "none";


void Logger::init(std::ostream& out,
				  const Level& level,
				  const Description& descr,
				  const bool& displayInitMsg)
{
	static Logger instance(out, level, descr, displayInitMsg);
}


Logger& Logger::getInstance(std::ostream& out,
							const Level& level,
							const Logger::Description& descr,
							const bool& displayInitMsg)
{
	init(out, level, descr, displayInitMsg);
	return (*_instance);
}


Logger& Logger::out(const Logger::Level& level,
					const char* funcname,
					const char* filename,
					const int& linenum)
{
	return getInstance()._out(level, funcname, filename, linenum);
}


Logger& Logger::debug(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return getInstance()._debug(funcname, filename, linenum);
}


Logger& Logger::info(const char* funcname,
					 const char* filename,
					 const int& linenum)
{
	return getInstance()._info(funcname, filename, linenum);
}


Logger& Logger::warning(const char* funcname,
						const char* filename,
						const int& linenum)
{
	return getInstance()._warning(funcname, filename, linenum);
}


Logger& Logger::error(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return getInstance()._error(funcname, filename, linenum);
}


Logger& Logger::fatal(const char* funcname,
					  const char* filename,
					  const int& linenum)
{
	return getInstance()._fatal(funcname, filename, linenum);
}


Logger& Logger::end()
{
	return getInstance()._end();
}


std::string Logger::basename(const char* filepath)
{
	std::string path = filepath;
	size_t sep_pos = path.rfind('/') + 1;

	if (sep_pos == std::string::npos)
		return std::move(path);

	return std::move(path.substr(sep_pos, path.size() - sep_pos));
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

		case Level::FATAL:
			return Level::ERROR;

		case Level::NONE:
		default:
			return Level::DEBUG;
	}
}


Logger::Logger(std::ostream& output,
			   const Level& level,
			   const Description& descr,
			   const bool& displayInitMsg)
	: _output(output),
	  _level(validateInitialLevel(level)),
	  _description(descr),
	  _displayDestroyMsg(displayInitMsg)
{
	_instance = this;

	if (displayInitMsg)
	{
		_info(__FUNCTION__, __FILE__, __LINE__) << CONSTRUCTOR_MESSAGE;
		_end();
	}
}


Logger::~Logger()
{
	if (_displayDestroyMsg)
	{
		_info(__FUNCTION__, __FILE__, __LINE__) << DESTRUCTOR_MESSAGE;
		_end();
	}
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
						<< "] [" << funcname << "] ";
				break;
			case Description::FULL:
				_output << '[' << level
						<< "] [" << funcname
						<< "] (in " << basename(filename) << ':' << linenum << ") ";
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
