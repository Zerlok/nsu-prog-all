#ifndef __ARGVPARSER_H__
#define __ARGVPARSER_H__


#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


static const string LONG_FLAG_START = "--";
static const string SHORT_FLAG_START = "-";
static const string EMPTY_ARG = "";


class ArgvArgument
{
	public:
		// Constructors / Destructor.
		ArgvArgument(char *value) : _value(value) {}
		ArgvArgument(const string &value) : _value(value) {}
		virtual ~ArgvArgument() {}

		// Operators.
		ArgvArgument &operator=(const ArgvArgument &arg)
		{
			_value = arg._value;

			return (*this);
		}

		// Getters.
		const string &get_value() const { return _value; }

	private:
		// Fields.
		string _value;
};


class ArgvFlag : public ArgvArgument
{
	public:
		// Constructors / Destructor.
		ArgvFlag(char *name) : ArgvArgument(name), _params() {}
		ArgvFlag(const ArgvFlag &flg) : ArgvArgument(flg), _params(flg._params) {}
		~ArgvFlag() {}

		// Operators.
		const string &operator[](int i) const
		{
			if (_params.size() == 0)
				return EMPTY_ARG;

			int idx = (i > 0)
					? (i % _params.size())
					: (0);

			return (_params[idx]).get_value();
		}

		// Methods.
		void push_param(const ArgvArgument& param) { _params.push_back(param); }
		const vector<ArgvArgument>&get_params() const { return _params; }
		int get_params_num() const { return _params.size(); }

	private:
		// Fields.
		vector<ArgvArgument> _params;
};


template <class DataClass>
class ArgvParser
{
	public:
		// Types.
		typedef	void (*t_parser_fptr)(const ArgvFlag&, DataClass&);

		// Constructors / Destructor.
		ArgvParser() : _parsers(), _flags(), _data() {}
		~ArgvParser() {}

		// Methods.
		void register_flag_parser(const string &flagname, t_parser_fptr parser_func)
		{
			_parsers.insert({flagname, parser_func});
		}

		void register_flag_parser(const string &flagname1, const string &flagname2, t_parser_fptr parser_func)
		{
			register_flag_parser(flagname1, parser_func);
			register_flag_parser(flagname2, parser_func);
		}

		void unregister_flag_parser(const string &flagname)
		{
			_parsers.erase(flagname);
		}

		DataClass parse_all(int argc, char **argv)
		{
			ArgvFlag flag = ArgvFlag(argv[0]);

			for (int i = 1; i < argc; i++)
			{
				if (is_flag(argv[i]))
				{
					_flags.push_back(flag);
					flag = ArgvFlag(argv[i]);
				}
				else
					flag.push_param(ArgvArgument(argv[i]));
			}
			_flags.push_back(flag);

			for (const ArgvFlag flag : _flags)
			{
				auto const pair = _parsers.find(flag.get_value());

				if (pair != _parsers.end())
					pair->second(flag, _data);

				else
					cerr << "Unknown flag: " << flag.get_value() << endl;
			}

			return _data;
		}

		bool is_flag(const string &arg)
		{
			return ((arg.find(LONG_FLAG_START) == 0)
					|| (arg.find(SHORT_FLAG_START) == 0));
		}

	private:
		// Fields.
		unordered_map<string, t_parser_fptr> _parsers;
		vector<ArgvFlag> _flags;
		DataClass _data;
};


// __ARGVPARSER_H__
#endif
