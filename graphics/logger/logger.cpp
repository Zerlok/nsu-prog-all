#include "logger.hpp"


#include <sys/time.h>


// ----------------------- LOGGER (public) ----------------------- //

const std::string& Logger::EMPTY_STRING = "null";


Logger& Logger::instance(const std::string& filename,
						 const int& linenum,
						 std::ostream& out)
{
	static Logger instance(filename, linenum, out);
	return instance;
}


int Logger::init(const std::string& filename,
				 const int& linenum,
				 std::ostream& out,
				 const Level& level,
				 const int& description)
{
	instance(filename, linenum, out);
	return setModule(filename, level, description);
}


int Logger::setDefalt(const Logger::Level& level,
					  const int& description)
{
	Format& df = _defaultFormat();
	return df.update(level, description) ? 1 : 0;
}


int Logger::setModule(const std::string& filename,
					  const Logger::Level& level,
					  const int& description)
{
	Modules& modules = _getModules();
	const Modules::const_iterator it = modules.find(filename);
	if (it != modules.end())
		return 0;

	modules.insert({filename, {level, description}});
	return 1;
}


int Logger::setGlobal(const Logger::Level& level,
					  const int& description)
{
	Format& gf = _globalFormat();
	return gf.update(level, description) ? 1 : 0;
}


Logger& Logger::out(const std::string& filename,
					const int& linenum,
					const std::string& funcname,
					const Level& localLevel)
{
	Logger& l = instance(filename, linenum);
	Format& localFormat = l._localFormat;
	if (localFormat.isPrintable())
		return l;

	const Modules& modules = _getModules();
	const auto it = modules.find(filename);

	if (_globalFormat().isValid())
		localFormat = _globalFormat().validate(localLevel);

	else if (it != modules.end())
		localFormat = (*it).second.validate(localLevel);

	else
		localFormat = _defaultFormat().validate(localLevel);

	if (localFormat.isPrintable())
	{
		l._localFormat = localFormat;
		l._out(filename, linenum, funcname, localLevel);
	}

	return l;
}


Logger& Logger::operator<<(Logger& (*manipulator)(Logger&))
{
	return manipulator(*this);
}


Logger& Logger::operator<<(std::ostream&(*manipulator)(std::ostream&))
{
	if (_localFormat.isPrintable())
		manipulator(_output);

	return (*this);
}


Logger& Logger::endl(Logger& logger)
{
	return logger._endl();
}


// ----------------------- LOGGER (private) ----------------------- //

Logger::Logger(const std::string& filename,
			   const int& linenum,
			   std::ostream& output)
	: _output(output),
	  _localFormat(_defaultFormat())
{
	_localFormat.setPrintable(true);
	_out(filename, linenum, __FUNCTION__, Level::INFO)
			<< "========== LOGGER STARTED ==========";
	_endl();
}


Logger::~Logger()
{
	_localFormat = _defaultFormat();
	_localFormat.setPrintable(true);
	Logger& l = _out(__FILE__, __LINE__, __FUNCTION__, Level::INFO);

	const Format& df = _defaultFormat();
	Modules& mf = _getModules();
	const Format& gf = _globalFormat();
	l << "========== LOGGER STOPPED ==========" << std::endl
	  << "Default format: " << df.getLevel() << ", " << df.getDescription() << std::endl
	  << "Global format: " << gf.getLevel() << ", " << gf.getDescription() << std::endl
	  << "Registred modules (" << mf.size() << "):" << std::endl;

	for (auto it : mf)
		l << it.first << " --- "
		  << (it.second).getLevel() << ", "
		  << (it.second).getDescription()
		  << std::endl;

	_endl();
}


Logger& Logger::_out(const std::string& filename,
					 const int& linenum,
					 const std::string& funcname,
					 const Level& localLevel)
{
	if (_localFormat.hasTimestamp())
		_output << '[' << _timestamp << "] ";

	if (_localFormat.hasModuleName())
		_output << '[' << _basename(filename) << ':' << linenum << "] ";

	if (_localFormat.hasFunctionName())
		_output << '[' << funcname << "] ";

	if (_localFormat.hasLevel())
		_output << '[' << localLevel << "] ";

	return (*this);
}


Logger& Logger::_endl()
{
	if (_localFormat.isPrintable())
		_output << std::endl;

	_localFormat.setPrintable(false);
	return (*this);
}


std::string Logger::_basename(const std::string& filepath)
{
	std::string path = filepath;
	size_t pos = path.rfind('/') + 1;

	if (pos == std::string::npos)
		return std::move(path);

	return std::move(path.substr(pos, path.size() - pos));
}


std::ostream& Logger::_timestamp(std::ostream& out)
{
	static struct timeval time;
	gettimeofday(&time, NULL);
	return out << time.tv_sec << '.' << time.tv_usec;
}


Logger::Level Logger::_validateLevel(const Logger::Level& level)
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


Logger::Format& Logger::_defaultFormat()
{
	static Format instance {Level::INFO, loggerDescriptionFull, true};
	return instance;
}


Logger::Modules& Logger::_getModules()
{
	// FIXME: instance destroying in another thread.
	static Modules instance;
	return instance;
}


Logger::Format& Logger::_globalFormat()
{
	static Format instance {Level::ERROR, 0, false};
	return instance;
}


// ----------------------- LOGGER::LEVEL ----------------------- //

std::ostream& operator<<(std::ostream& out,
						 const Logger::Level& level)
{
	switch (level)
	{
		case Logger::Level::NONE:
			return out << "NONE";
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


// ----------------------- LOGGER::FORMAT ----------------------- //

Logger::Format::Format(const Logger::Level& level,
					   const int& descriptionMask,
					   const bool& isValid)
	: _isPrintable(false),
	  _level(isValid ? level : Logger::Level::NONE),
	  _description(isValid ? descriptionMask : 0)
{
}


Logger::Format::Format(const Logger::Format& f)
	: _isPrintable(f._isPrintable),
	  _level(f._level),
	  _description(f._description)
{
}


Logger::Format::Format(Logger::Format&& f)
	: _isPrintable(std::move(f._isPrintable)),
	  _level(std::move(f._level)),
	  _description(std::move(f._description))
{
}


Logger::Format::~Format()
{
}


Logger::Format& Logger::Format::operator=(const Logger::Format& f)
{
	_isPrintable = f._isPrintable;
	_level = f._level;
	_description = f._description;

	return (*this);
}


Logger::Format& Logger::Format::operator=(Logger::Format&& f)
{
	_isPrintable = std::move(f._isPrintable);
	_level = std::move(f._level);
	_description = std::move(f._description);

	return (*this);
}


bool Logger::Format::isPrintable() const
{
	return _isPrintable;
}


bool Logger::Format::isValid() const
{
	return (_level != Logger::Level::NONE);
}


bool Logger::Format::hasTimestamp() const
{
	return (_description & Description::TIMESTAMP);
}


bool Logger::Format::hasModuleName() const
{
	return (_description & Description::MODULE);
}


bool Logger::Format::hasFunctionName() const
{
	return (_description & Description::FUNCTION);
}


bool Logger::Format::hasLevel() const
{
	return (_description & Description::LEVEL);
}


const Logger::Level& Logger::Format::getLevel() const
{
	return _level;
}


const int& Logger::Format::getDescription() const
{
	return _description;
}


Logger::Format Logger::Format::validate(const Logger::Level& level) const
{
	Format localFormat {level, _description};
	localFormat.setPrintable(level >= _level);
	return std::move(localFormat);
}


bool Logger::Format::update(const Logger::Level& level,
							const int& description)
{
	if (level >= _level)
		return false;

	_level = level;
	_description = (description == 0)
			? _description
			: description;

	return true;
}


void Logger::Format::setPrintable(bool val)
{
	_isPrintable = val;
}
