#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__


#include <iostream>
#include <string>
#include <unordered_map>


class Logger
{
	public:
		// Inner classes.
		/*
		 * Logger messages levels.
		 */
		enum class Level
		{
			NONE		= 1000,
			DEBUG		= 0100,
			INFO		= 0200,
			WARNING		= 0300,
			ERROR		= 0400,
			FATAL		= 0500,
		};

		/*
		 * Log messages format is:
		 * [timestamp] [module name] [function name] [level] message
		 * Description encodes in message masks.
		 */
		enum Description
		{
			TIMESTAMP	= 0b1000,
			MODULE		= 0b0100,
			FUNCTION	= 0b0010,
			LEVEL		= 0b0001,
		};

	private:
		class Format
		{
			public:
				Format(const Level& level = Level::NONE,
					   const int& descriptionMask = 0,
					   const bool& isValid = true);
				Format(const Format& f);
				Format(Format&& f);
				~Format();

				Format& operator=(const Format& f);
				Format& operator=(Format&& f);

				bool isPrintable() const;
				bool isValid() const;
				bool hasTimestamp() const;
				bool hasModuleName() const;
				bool hasLinenum() const;
				bool hasFunctionName() const;
				bool hasLevel() const;

				const Level& getLevel() const;
				const int& getDescription() const;

				Format validate(const Level& level) const;
				bool update(const Level& level,
							const int& description = 0);

				void setPrintable(bool val);

			private:
				bool _isPrintable;
				Level _level;
				int _description;
		};

	public:
		using Modules = std::unordered_map<std::string, Format>;

		// Static methods.
		/*
		 * Get Logger instance itself.
		 */
		static Logger& instance(const std::string& filename = EMPTY_STRING,
								const int& linenum = 0,
								std::ostream& out = std::cout);
		/*
		 * Initialize Logger instance and prepare for message printing.
		 */
		static int init(const std::string& filename,
						const int& linenum,
						std::ostream& out,
						const Level& level,
						const int& description);
		/*
		 * Defines default messages minimal level and description.
		 */
		static int setDefalt(const Level& level,
							 const int& description);
		/*
		 * Defines module messages minimal level and description.
		 */
		static int setModule(const std::string& filename,
							 const Level& level,
							 const int& description);
		/*
		 * Defines global messages minimal level and description.
		 */
		static int setGlobal(const Level& level,
							 const int& description);

		/*
		 * Checks the current message (local) level to prepare it printing.
		 * First, it checks if module was registered and compares it's level (module) with local.
		 * If module was not registered, it compares local level with level declared in main.cpp (global).
		 */
		static Logger& out(const std::string& filename,
						   const int& linenum,
						   const std::string& funcname,
						   const Level& level);

		static Logger& endl(Logger& logger);

		// Operators.
		template<class T>
		Logger& operator<<(const T& t)
		{
			if (_localFormat.isPrintable())
				_output << t;

			return (*this);
		}

		Logger& operator<<(Logger& (*manipulator)(Logger&));
		Logger& operator<<(std::ostream& (*manipulator)(std::ostream&));

	private:
		// Static fields.
		static const std::string& EMPTY_STRING;

		// Static methods.
		static std::string _basename(const std::string& filename);
		static std::ostream& _timestamp(std::ostream& out);
		static Level _validateLevel(const Level& level);

		static Format& _defaultFormat();
		static Modules& _getModules();
		static Format& _globalFormat();

		// Constructor / Destructor.
		Logger(const std::string& filename,
			   const int& linenum,
			   std::ostream& output);
		~Logger();

		// Deleted constructors / operators. Because Singleton.
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		// Methods.
		/*
		 * Prints message header according to given format.
		 */
		Logger& _out(const std::string& filename,
					 const int &linenum,
					 const std::string& funcname,
					 const Level& localLevel);
		/*
		 * Flush message. (Analogous to std::endl)
		 */
		Logger& _endl();

		// Fields.
		std::ostream& _output;
		Format _localFormat;
};


std::ostream& operator<<(std::ostream& out, const Logger::Level& level);


#define logger_t static const int
#define loggerDescriptionFull (Logger::Description::LEVEL\
	| Logger::Description::FUNCTION\
	| Logger::Description::MODULE\
	| Logger::Description::TIMESTAMP)

#define loggerInit(out, level, descr) (Logger::init(__FILE__, __LINE__, out, level, descr))
#define loggerDefault(level, descr) (Logger::setDefalt(level, descr))
#define loggerModule(level, descr) (Logger::setModule(__FILE__, level, descr))
#define loggerGlobal(level, descr) (Logger::setGlobal(level, descr))

//#define __HERE__ __FILE__, __LINE__, __FUNCTION__
//#define lDebug (debug(__HERE__))
//#define lInfo (info(__HERE__))
//#define lWarning (warning(__HERE__))
//#define lError (error(__HERE__))
//#define lFatal (fatal(__HERE__))

#define logDebug (Logger::out(__FILE__, __LINE__, __FUNCTION__, Logger::Level::DEBUG))
#define logInfo (Logger::out(__FILE__, __LINE__, __FUNCTION__, Logger::Level::INFO))
#define logWarning (Logger::out(__FILE__, __LINE__, __FUNCTION__, Logger::Level::WARNING))
#define logError (Logger::out(__FILE__, __LINE__, __FUNCTION__, Logger::Level::ERROR))
#define logFatal (Logger::out(__FILE__, __LINE__, __FUNCTION__, Logger::Level::FATAL))
#define logEndl (Logger::endl)


#endif // __LOGGER_HPP__
