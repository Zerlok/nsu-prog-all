#ifndef __ARGVPARSER_H__
#define __ARGVPARSER_H__


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include "abstractparser.h"


// ----------------------- ArgvArgument ----------------------- //
class ArgvArgument
{
	public:
		// Constructors / Destructor.
		ArgvArgument()
			: _value() {}
		ArgvArgument(char *value)
			: _value(value) {}
		ArgvArgument(const string &value)
			: _value(value) {}
		virtual ~ArgvArgument() {}

		// Operators.
		bool operator==(const char *value) const { return !(_value.compare(value)); }
		bool operator==(const string &value) const { return !(_value.compare(value)); }
		bool operator!=(const char *value) const { return !(this->operator==(value)); }
		bool operator!=(const string &value) const { return !(this->operator==(value)); }

		// Getters.
		const string &get_value() const { return _value; }

	protected:
		// Fields.
		string _value;
};


// ----------------------- ArgvFlag ----------------------- //
class ArgvFlag : public ArgvArgument
{
	public:
		// Static fields.
		static const string short_flag_start;
		static const string long_flag_start;
		static const string short_help_flag;
		static const string long_help_flag;
		static const ArgvArgument empty_argument;

		// Static methods.
		static bool is_flag(const ArgvArgument &arg);
		static bool is_help_flag(const ArgvArgument &arg);

		// Constructors / Destructor.
		ArgvFlag()
			: ArgvArgument(),
			  _params() {}
		ArgvFlag(char *name)
			: ArgvArgument(name),
			  _params() {}
		ArgvFlag(const ArgvArgument &arg)
			: ArgvArgument(arg),
			  _params() {}
		ArgvFlag(const ArgvFlag &flg)
			: ArgvArgument(flg),
			  _params(flg._params) {}
		~ArgvFlag() {}

		// Operators.
		ArgvArgument &operator=(const ArgvFlag &flag)
		{
			_value = flag._value;
			_params = flag._params;

			return (*this);
		}
		const string &operator[](int i) const { return get(i).get_value(); }

		// Getters.
		int get_params_num() const { return _params.size(); }
		const vector<ArgvArgument> &get_params() const { return _params; }
		const ArgvArgument &get(int i) const
		{
			return ((i >= 0)
					&& (unsigned(i) < _params.size()))
					? _params[i]
					: empty_argument;
		}

		// Methods.
		void push_param(const ArgvArgument& param) { _params.push_back(param); }

	private:
		// Fields.
		vector<ArgvArgument> _params;
};

const string ArgvFlag::short_flag_start = "-";
const string ArgvFlag::long_flag_start = "--";
const string ArgvFlag::short_help_flag = "-h";
const string ArgvFlag::long_help_flag = "--help";
const ArgvArgument ArgvFlag::empty_argument = ArgvArgument(string(""));
bool ArgvFlag::is_flag(const ArgvArgument &arg)
{
	const string &value = arg.get_value();
	return ((value.find(long_flag_start) == 0)
			|| (value.find(short_flag_start) == 0));
}
bool ArgvFlag::is_help_flag(const ArgvArgument &arg)
{
	const string &value = arg.get_value();
	return ((value.find(short_help_flag) == 0)
			|| (value.find(long_help_flag) == 0));
}


// ----------------------- ArgvParser----------------------- //
namespace parsing_messages
{
	// Messages.
	static const string msg_help_by_default = "*** GENERATED HELP MESSAGE (enabled by deafult) ***";
	static const string msg_known_flags = "Flags:";
	static const string msg_program_usage = "Usage: ";

	// Errors.
	static const string err_unknown_flag = "Unknown flag ";
}

enum class ParserAction
{
	continue_parsing = 0,
	stop_parsing_with_ok = 1,
	stop_parsing_with_err = 2,
};

template <class Data>
class ArgvParser : public AbstractParser<Data>
{
	public:
		// Types.
		/*
		 * Pointer to flag parsers functions.
		 * Functions of this type will be called by parser when flag this function
		 * regestered to has been read.
		 * pointer to function signature: void parser_fp(const ArgvFlag&, Data&);
		 */
		typedef	ParserAction(*t_flag_parser_func_ptr)(const ArgvFlag&, Data&);

		/*
		 * Flag parsers map type.
		 * Key: flag name, Value: pointer to flag parser function.
		 */
		typedef unordered_map<string, t_flag_parser_func_ptr> t_parsers;

		// Constructors / Destructor.
		ArgvParser(int argc=0, char *argv[]=nullptr)
			: AbstractParser<Data>(),
			  _flag_parsers(),
			  _flags(),
			  _args(),
			  _main_flag_parser(nullptr),
			  _main_flag(nullptr),
			  _is_help_flag_read(false)
		{
			set_arguments(argc, argv);
		}
		ArgvParser(const t_parsers &parsers)
			: AbstractParser<Data>(),
			  _flag_parsers(parsers),
			  _flags(),
			  _args(),
			  _main_flag_parser(nullptr),
			  _main_flag(nullptr),
			  _is_help_flag_read(false) {}
		~ArgvParser()
		{
			delete _main_flag;
		}

		// Getters.
		const string &get_main_name() const { return _main_name; }
		const t_parsers &get_flag_parsers() const { return _flag_parsers; }

		// Methods.
		bool register_flag_parser(const string &flagname, t_flag_parser_func_ptr parser_func)
		{
			if (!(ArgvFlag::is_flag(flagname))
					|| (parser_func == nullptr))
				return false;

			this->_is_input_valid = false;
			_flag_parsers.insert(make_pair(flagname, parser_func));
			return true;
		}

		bool set_arguments(int argc, char *argv[])
		{
			if ((argc <= 0)
					|| (argv == nullptr))
				return false;

			_args.clear();
			this->_is_input_valid = false;

			_main_name = argv[0];
			for (int i = 0; i < argc; ++i)
				_args.push_back(ArgvArgument(argv[i]));

			return true;
		}

		bool set_main_flag_parser(t_flag_parser_func_ptr main_flag_parser)
		{
			if (_main_flag_parser != nullptr)
				return false;

			_main_flag_parser = main_flag_parser;
			return true;
		}

		ParserAction helpper() const
		{
			cout << parsing_messages::msg_help_by_default << endl;
			cout << parsing_messages::msg_program_usage << _main_name << endl;

			if (_flag_parsers.empty())
				return ParserAction::stop_parsing_with_ok;

			cout << parsing_messages::msg_known_flags << endl;
			for (auto const &it : _flag_parsers)
				cout << "\t" << it.first << endl;

			return ParserAction::stop_parsing_with_ok;
		}

		// Overriden methods.
		bool parse_input() override
		{
			// Check for input validation.
			if (!validate_input())
				return false;

			// Check for help flag by default.
			if (_is_help_flag_read)
				switch (helpper())
				{
					case (ParserAction::stop_parsing_with_ok):
						return true;
					case (ParserAction::stop_parsing_with_err):
						return false;
					default:
						break;
				}

			// Parse main flag firstly.
			if ((_main_flag != nullptr)
					&& (_main_flag_parser != nullptr))
				switch (_main_flag_parser(*_main_flag, this->_parsed_data))
				{
					case (ParserAction::stop_parsing_with_ok):
						return true;
					case (ParserAction::stop_parsing_with_err):
						return false;
					default:
						break;
				}

			// Parse through rest flags.
			for (const ArgvFlag &flag : _flags)
			{
				t_flag_parser_func_ptr flag_parser = (_flag_parsers.find(flag.get_value()))->second;
				// Call flag parser for current flag.
				switch (flag_parser(flag, this->_parsed_data))
				{
					case (ParserAction::stop_parsing_with_ok):
						return true;
					case (ParserAction::stop_parsing_with_err):
						return false;
					default:
						break;
				}
			}

			return true;
		}

		bool validate_input() override
		{
			// Save name of called program.
			_main_flag = new ArgvFlag(_args[0]);
			_main_name = _main_flag->get_value();

			// Cycle through all arguments.
			ArgvFlag *flag = nullptr;
			for (int i = 1; i < _args.size(); ++i)
			{
				const ArgvArgument &arg = _args[i];

				// Is current argument a flag.
				if (ArgvFlag::is_flag(arg))
				{
					// Save current flag.
					if (flag != nullptr)
					{
						_flags.push_back(*flag);
						delete flag;
					}

					// Check for parser for new flag (arg).
					if (_flag_parsers.find(arg.get_value()) == _flag_parsers.end())
					{
						// Is help flag.
						if (ArgvFlag::is_help_flag(arg))
						{
							_is_help_flag_read = true;
							this->_is_input_valid = true;

							return true;
						}

						// Unknown flag.
						cerr << parsing_messages::err_header_validating
								<< parsing_messages::err_unknown_flag
								<< arg.get_value()
								<< endl;
						return false;
					}

					// Set current argument as a new flag.
					flag = new ArgvFlag(arg);
				}
				// If current flag was not created yet - add current argument to main flag.
				else if (flag == nullptr)
				{
					// Check for main flag parser.
					if (_main_flag_parser == nullptr)
					{
						cerr << parsing_messages::err_header_validating
								<< parsing_messages::err_too_many_parameters
								<< parsing_messages::msg_no_parameters_required
								<< endl;
						return false;
					}

					_main_flag->push_param(arg);
				}

				// Push argument to current flag.
				else
					flag->push_param(arg);
			}

			// Push last flag.
			if (flag != nullptr)
			{
				_flags.push_back(*flag);
				delete flag;
			}

			// Input is valid - ok.
			this->_is_input_valid = true;
			return true;
		}

	private:
		// Fields.
		t_parsers _flag_parsers;
		vector<ArgvFlag> _flags;
		vector<ArgvArgument> _args;

		t_flag_parser_func_ptr _main_flag_parser;
		ArgvFlag *_main_flag;
		string _main_name;

		bool _is_help_flag_read;
};


// __ARGVPARSER_H__
#endif
