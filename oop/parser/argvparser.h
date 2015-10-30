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
		ArgvArgument(char *value) : _value(value) {}
		ArgvArgument(const string &value) : _value(value) {}
		virtual ~ArgvArgument() {}

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
		static const ArgvArgument empty_argument;

		// Static methods.
		static bool is_flag(const string &value);
		static bool is_flag(const ArgvArgument &arg);

		// Constructors / Destructor.
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
const ArgvArgument ArgvFlag::empty_argument = ArgvArgument(string(""));
bool ArgvFlag::is_flag(const string &value)
{
	return ((value.find(long_flag_start) == 0)
			|| (value.find(short_flag_start) == 0));
}
bool ArgvFlag::is_flag(const ArgvArgument &arg) { return is_flag(arg.get_value()); }


// ----------------------- ArgvParser----------------------- //
namespace parsing_messages
{
	// Messages.
	static const string msg_help_default = "*** DEFAULT HELP MESSAGE ***\n";
	static const string msg_usage = "Usage: ";

	// Errors.
	static const string err_unknown_flag = "(unknown flag): ";
}

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
		typedef	void (*parser_fp)(const ArgvFlag&, Data&);
		/*
		 * Flag parsers map type.
		 * Key: flag name, Value: pointer to flag parser function.
		 */
		typedef unordered_map<string, parser_fp> t_parsers;

		// Constructors / Destructor.
		ArgvParser(int argc=0, char *argv[]=nullptr)
			: AbstractParser<Data>(),
			  _parsers(),
			  _flags(),
			  _args() { set_arguments(argc, argv); }
		ArgvParser(const t_parsers &parsers)
			: AbstractParser<Data>(),
			  _parsers(parsers),
			  _flags(),
			  _args() {}
		~ArgvParser() {}

		// Methods.
		void register_flag_parser(const string &flagname, parser_fp parser_func)
		{
			_parsers.insert(make_pair(flagname, parser_func));
		}

		bool set_arguments(int argc, char *argv[])
		{
			if ((argc <= 0)
					|| (argv == nullptr))
				return false;

			_args.clear();
			this->_is_input_valid = false;
			this->_is_input_validated = false;

			_main = argv[0];
			for (int i = 0; i < argc; ++i)
				_args.push_back(ArgvArgument(argv[i]));

			return true;
		}

		void print_help() const
		{
			cout << parsing_messages::msg_help_default << endl;
			cout << parsing_messages::msg_usage << _main << "[PARAMS] [FLAGS]" << endl;
			cout << "Flags:" << endl;

			for (auto const pair : _parsers)
				cout << "   " << pair.first << endl;
		}

		// Overriden methods.
		bool parse_input() override
		{
			if (validate_input())
				return false;

			ArgvFlag flag = ArgvFlag(_args[0]);
			_main = flag.get_value();

			for (const ArgvArgument &arg : _args)
			{
				if (ArgvFlag::is_flag(arg))
				{
					_flags.push_back(flag);
					flag = ArgvFlag(arg);
				}
				else
					flag.push_param(arg);
			}
			_flags.push_back(flag);

			for (const ArgvFlag flag : _flags)
			{
				auto const pair = _parsers.find(flag.get_value());

				if (pair != _parsers.end())
				{
					pair->second(flag, this->_parsed_data);
				}
				else if (!flag.get_value().compare("--help"))
				{
					print_help();
					return false;
				}
				else
				{
					cerr << parsing_messages::err_header_validating
						 << parsing_messages::err_unknown_flag
						 << flag.get_value()
						 << endl;

					return false;
				}
			}

			return true;
		}

		bool validate_input() override
		{
			if (this->_is_input_validated)
				return this->_is_input_valid;

			return this->_is_input_valid;
		}

	private:
		// Fields.
		t_parsers _parsers;
		vector<ArgvFlag> _flags;
		vector<ArgvArgument> _args;
		string _main;
};


// __ARGVPARSER_H__
#endif
