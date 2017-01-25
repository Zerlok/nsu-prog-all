#ifndef __SEARCH_REPLACE_COMMAND_H__
#define __SEARCH_REPLACE_COMMAND_H__


#include "command.h"
#include "stringutils.h"


class SearchReplaceCommand : public Command
{
	public:
		class Prototype;

		SearchReplaceCommand(const std::string& substr)
			: Command(Type::data_manipulation),
			  _substr(substr),
			  _repl(),
			  _use_buffer(true) {}
		SearchReplaceCommand(const std::string& substr, const std::string& repl)
			: Command(Type::data_manipulation),
			  _substr(substr),
			  _repl(repl),
			  _use_buffer(false) {}
		~SearchReplaceCommand() {}

		size_t subfind(const std::string& data, const std::string& substr) const
		{
			size_t i = 0;
			size_t j;
			const size_t subsize = substr.size();
			while (i < data.size())
			{
				for (j = 0; j < subsize; ++j)
					if (data[i] != substr[j])
						break;

				if (j == subsize)
					return i;

				i += j + 1;
			}

			return i;
		}

		Errors validate(const std::string& data, const std::string&) const override
		{
			Errors errs;

			if ((data.size() < _substr.size())
					|| (data.find(_substr) == std::string::npos))
			{
				std::stringstream ss;
				ss << "'" << _substr << "' is not a substring of '" << data << "'";
				errs.push_back(Error("Substring not found!", ss.str()));
			}

			return std::move(errs);
		}

		Result execute(const std::string& data, std::string& buffer) override
		{
			Result res(data, validate(data, buffer));

			if (!res)
				return std::move(res);


			if (_use_buffer)
				_repl = buffer;

			// Taken from task15-code-highlight (also there are stringutils' google tests located).
			stringutils::search_replace_all(res.data, _substr, _repl);

			return std::move(res);
		}

	private:
		std::string _substr;
		std::string _repl;
		bool _use_buffer;
};


class SearchReplaceCommand::Prototype : public AbstractPrototype
{
	public:
		Prototype()
			: AbstractPrototype() {}
		Prototype(const Strings& args)
			: AbstractPrototype(args) {}
		~Prototype() {}

		Result construct() const override
		{
			Result res;

			switch (arguments.size())
			{
				case 2:
					res.ptr = new SearchReplaceCommand(arguments[0], arguments[1]);
					break;

				case 1:
					res.ptr = new SearchReplaceCommand(arguments[0]);
					break;

				case 0:
				default:
					res.errors.push_back(Error(Error::type::invalid_arguments_num, "At least one argument is required."));
					break;
			}

			return std::move(res);
		}
};


// __SEARCH_REPLACE_COMMAND_H__
#endif
