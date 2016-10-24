#include "logger.hpp"


#include <sys/time.h>


const std::string& Logger::EMPTY_STRING = "null";


Logger& Logger::getInstance(const std::string& filename,
							const int& linenum, std::ostream& out,
							const Level& level,
							const Logger::Description& descr,
							const bool& displayInitMsg)
{
	static Logger instance(out, level, descr, filename, linenum, displayInitMsg);
	return instance;
}


Logger& Logger::addModule(const std::string& filename,
						  const Logger::Level& level,
						  const Logger::Description& description)
{
	const Modules::const_iterator it = getModules().find(filename);
	if (it == getModules().end())
		getModules().insert({filename, {level, description}});

	return getInstance();
}


Logger& Logger::debug(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum)
{
	return _out(Level::DEBUG, _description, funcname, filename, linenum);
}


Logger& Logger::info(const std::string& funcname,
					 const std::string& filename,
					 const int& linenum)
{
	return _out(Level::INFO, _description, funcname, filename, linenum);
}


Logger& Logger::warning(const std::string& funcname,
						const std::string& filename,
						const int& linenum)
{
	return _out(Level::WARNING, _description, funcname, filename, linenum);
}


Logger& Logger::error(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum)
{
	return _out(Level::ERROR, _description, funcname, filename, linenum);
}


Logger& Logger::fatal(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum)
{
	return _out(Level::FATAL, _description, funcname, filename, linenum);
}


Logger& Logger::module(const std::string& funcname,
						const std::string& filename,
						const int& linenum)
{
	const Modules::const_iterator it = getModules().find(filename);
	if (it == getModules().end())
		return _out(_level, _description, funcname, filename, linenum);

	const Format& moduleFormat = it->second;
	return _out(moduleFormat.first, moduleFormat.second, funcname, filename, linenum);
}


Logger::Modules& Logger::getModules()
{
	static Modules instance;
	return instance;
}


Logger& Logger::endl()
{
	return getInstance()._end();
}


std::string Logger::basename(const std::string& filepath)
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
			   const std::string& filename,
			   const int& linenum,
			   const bool& displayInitMsg)
	: _output(output),
	  _level(validateInitialLevel(level)),
	  _description(descr),
	  _displayDestroyMsg(displayInitMsg)
{
	if (displayInitMsg)
	{
		_out(Level::INFO, Description::FULL, __FUNCTION__, filename, linenum)
				<< "========== LOGGER STARTED ==========";
		_end();
	}
}


Logger::~Logger()
{
	if (_displayDestroyMsg)
	{
		Logger& l = info(__FUNCTION__, __FILE__, __LINE__) << " registred modules:" << std::endl;
		for (auto it : getModules())
			l << it.first << " - "
			  << (it.second).first << ", "
			  << int((it.second).second)
			  << std::endl;
		_end();

		info(__FUNCTION__, __FILE__, __LINE__)
				<< "========== LOGGER STOPPED ==========";
		_end();
	}
}


Logger& Logger::_out(const Level& level,
					 const Description& descr,
					 const std::string& funcname,
					 const std::string& filename,
					 const int& linenum)
{
	if (_isCurrentLevelAlreadySet())
		return (*this);

	_current_message_level = level;
	if (!_isCurrentLevelValid())
		return (*this);

	_output << '[' << addTimestamp << "] ";

	switch (descr)
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

	return (*this);
}


Logger& Logger::_end()
{
	if (_isCurrentLevelValid())
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
	if (_isCurrentLevelValid())
		manipulator(_output);

	return (*this);
}


bool Logger::_isCurrentLevelValid() const
{
	return (int(_current_message_level) >= int(_level));
}


bool Logger::_isCurrentLevelAlreadySet() const
{
	return (_current_message_level != Level::NONE);
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
