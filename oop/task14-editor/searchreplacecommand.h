#ifndef __SEARCH_REPLACE_COMMAND_H__
#define __SEARCH_REPLACE_COMMAND_H__


#include "command.h"


class SearchReplaceCommand : public Command
{
	public:
		SearchReplaceCommand(const std::string& substr, const std::string& repl)
			: Command(Type::data_manipulation),
			  _substr(substr),
			  _repl(repl) {}
		SearchReplaceCommand(const Strings& args)
			: Command(Type::data_manipulation),
			  _substr(args[0]),
			  _repl(args[1]) {}
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
			if ((data.size() < _substr.size())
					|| (data.find(_substr) == std::string::npos))
			{
				std::stringstream ss;
				ss << "'" << _substr << "' is not a substring of '" << data << "'" << std::endl;
				return std::move(Errors({Error("Substring not found!", ss.str())}));
			}

			return std::move(Errors());
		}

		Result execute(const std::string& data, std::string& buffer) override
		{
			Result res(data, validate(data, buffer));

			if (!res)
				return std::move(res);

			const size_t pos = data.find(_substr);
			res.data.erase(pos, _substr.size());
			res.data.insert(pos, _repl);

			return std::move(res);
		}

	private:
		std::string _substr;
		std::string _repl;
};


// __SEARCH_REPLACE_COMMAND_H__
#endif
