#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__


#include <iostream>
#include <string>
#include <sys/time.h>


class Logger
{
	public:
		enum class Level
		{
			NONE = 0,
			DEBUG,
			INFO,
			WARNING,
			ERROR,
			FATAL,
		};

		static void init(
				std::ostream& _out = std::cout,
				const Level& level = Level::INFO);
		static Logger& getInstance(
				std::ostream& _out,
				const Level& level);

		static Logger& out(const Level& level,
						   const char* funcname = nullptr,
						   const char* filename = nullptr,
						   const int& linenum = -1);
		static Logger& debug(const char* funcname = nullptr,
							 const char* filename = nullptr,
							 const int& linenum = -1);
		static Logger& info(const char* funcname = nullptr,
							const char* filename = nullptr,
							const int& linenum = -1);
		static Logger& warning(const char* funcname = nullptr,
							   const char* filename = nullptr,
							   const int& linenum = -1);
		static Logger& error(const char* funcname = nullptr,
							 const char* filename = nullptr,
							 const int& linenum = -1);
		static Logger& fatal(const char* funcname = nullptr,
							 const char* filename = nullptr,
							 const int& linenum = -1);
		static Logger& end();

		Logger& operator<<(Logger& (*manipulator)(void));

		template<class T>
		Logger& operator<<(const T& t)
		{
			if (validateCurrentLevel())
				_output << t;
			return (*this);
		}

	private:
		static const std::string CONSTRUCTOR_MESSAGE;
		static const std::string DESTRUCTOR_MESSAGE;

		static Logger* _instance;

		static std::ostream& strTimestamp(std::ostream& _out);
		static Level validateInitialLevel(const Level& level);

		Logger(std::ostream& output, const Level& level);
		~Logger();
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		Logger& _out(
				const Level &level,
				const char* funcname,
				const char* filename,
				const int &linenum);
		Logger& _debug(const char* funcname,
					   const char* filename,
					   const int& linenum);
		Logger& _info(const char* funcname,
					  const char* filename,
					  const int& linenum);
		Logger& _warning(const char* funcname,
						 const char* filename,
						 const int& linenum);
		Logger& _error(const char* funcname,
					   const char* filename,
					   const int& linenum);
		Logger& _fatal(const char* funcname,
					   const char* filename,
					   const int& linenum);
		Logger& _end();

		bool validateCurrentLevel() const;

		std::ostream& _output;
		Level _current_message_level;
		const Level _level;
};

std::ostream& operator<<(std::ostream& out, const Logger::Level& level);


#define logEnd (Logger::end)

#define logDebug (Logger::debug())
#define logInfo (Logger::info())
#define logWarning (Logger::warning())
#define logError (Logger::error())
#define logFatal (Logger::fatal())

#define logDebugFunc (Logger::debug(__FUNCTION__))
#define logInfoFunc (Logger::info(__FUNCTION__))
#define logWarningFunc (Logger::warning(__FUNCTION__))
#define logErrorFunc (Logger::error(__FUNCTION__))
#define logFatalFunc (Logger::fatal(__FUNCTION__))

#define logDebugFull (Logger::debug(__FUNCTION__, __FILE__, __LINE__))
#define logInfoFull (Logger::info(__FUNCTION__, __FILE__, __LINE__))
#define logWarningFull (Logger::warning(__FUNCTION__, __FILE__, __LINE__))
#define logErrorFull (Logger::error(__FUNCTION__, __FILE__, __LINE__))
#define logFatalFull (Logger::fatal(__FUNCTION__, __FILE__, __LINE__))


#endif // __LOGGER_HPP__
