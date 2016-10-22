#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__


#include <iostream>
#include <string>
#include <unordered_map>


class Logger
{
	public:
		// Inner classes.
		enum class Level
		{
			NONE = 0,
			DEBUG,
			INFO,
			WARNING,
			ERROR,
			FATAL,
		};

		enum class Description
		{
			LEVEL = 0,
			MESSAGE_ONLY,
			LEVEL_AND_FUNCTION,
			FULL,
		};

		// Static methods.
		static void init(const std::string& filename = EMPTY_STRING,
						 const int& linenum = 0,
						 std::ostream& out = std::cout,
						 const Level& level = Level::INFO,
						 const Description& descr = Description::LEVEL,
						 const bool& displayInitMsg = true);
		static Logger& getInstance(const std::string& filename = EMPTY_STRING,
								   const int& linenum = 0,
								   std::ostream& out = std::cout,
								   const Level& level = Level::INFO,
								   const Description& descr = Description::LEVEL,
								   const bool& displayInitMsg = true);
		static Logger& addModule(const std::string& filename,
								 const Level& level = Level::INFO,
								 const Description& description = Description::LEVEL);
		static Logger& endl();

		// Operators.
		Logger& operator<<(Logger& (*manipulator)(void));
		Logger& operator<<(std::ostream& (*manipulator)(std::ostream&));

		template<class T>
		Logger& operator<<(const T& t)
		{
			if (_isCurrentLevelValid())
				_output << t;
			return (*this);
		}

		// Methods.
		Logger& debug(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum);
		Logger& info(const std::string& funcname,
					 const std::string& filename,
					 const int& linenum);
		Logger& warning(const std::string& funcname,
						const std::string& filename,
						const int& linenum);
		Logger& error(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum);
		Logger& fatal(const std::string& funcname,
					  const std::string& filename,
					  const int& linenum);
		Logger& module(const std::string& funcname,
					   const std::string& filename,
					   const int& linenum);

	private:
		// Inner classes.
		using Format = std::pair<Logger::Level, Logger::Description>;
		using Modules = std::unordered_map<std::string, Format>;

		// Static.
		static const std::string EMPTY_STRING;

		static std::string basename(const std::string& filename);
		static std::ostream& addTimestamp(std::ostream& out);
		static Level validateInitialLevel(const Level& level);
		static Modules& _getModules();


		// Constructors / Destructor.
		Logger(std::ostream& output,
			   const Level& level,
			   const Description& descr,
			   const std::string& filename,
			   const int& linenum,
			   const bool& displayInitMsg);
		~Logger();
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		// Methods.
		Logger& _out(const Level &level,
					 const Description& descr,
					 const std::string& funcname,
					 const std::string& filename,
					 const int &linenum);
		Logger& _end();

		bool _isCurrentLevelValid() const;
		bool _isCurrentLevelAlreadySet() const;

		// Fields.
		std::ostream& _output;
		Level _current_message_level;
		const Level _level;
		const Description _description;
		const bool _displayDestroyMsg;
};

std::ostream& operator<<(std::ostream& out, const Logger::Level& level);


#define loggerType static Logger&
#define loggerInit(out, level, descr) (Logger::getInstance(__FILE__, __LINE__, out, level, descr))
#define loggerForModule(level, descr) (Logger::addModule(__FILE__, level, descr))

#define logDebug (Logger::getInstance(__FILE__, __LINE__).debug(__FUNCTION__, __FILE__, __LINE__))
#define logInfo (Logger::getInstance(__FILE__, __LINE__).info(__FUNCTION__, __FILE__, __LINE__))
#define logWarning (Logger::getInstance(__FILE__, __LINE__).warning(__FUNCTION__, __FILE__, __LINE__))
#define logError (Logger::getInstance(__FILE__, __LINE__).error(__FUNCTION__, __FILE__, __LINE__))
#define logFatal (Logger::getInstance(__FILE__, __LINE__).fatal(__FUNCTION__, __FILE__, __LINE__))
#define logModule (Logger::getInstance(__FILE__, __LINE__).module(__FUNCTION__, __FILE__, __LINE__))
#define logEndl (Logger::endl)


#endif // __LOGGER_HPP__
