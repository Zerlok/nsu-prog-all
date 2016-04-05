#ifndef __COPY_COMMAND_H__
#define __COPY_COMMAND_H__


#include <string>
#include <sstream>
#include "command.h"


class CopyCommand : public Command
{
	public:
		class Prototype : public AbstractPrototype
		{
			Prototype()
				: AbstractPrototype(Type::data_manipulation, 2) {}
			~Prototype() {}

			CopyCommand* construct(const Strings& args) override;
		};

		CopyCommand(const int& begin = 0, const int& end = -1)
			: Command(Type::data_manipulation),
			  _begin(begin),
			  _end(end) {}
		CopyCommand(const Strings& args)
			: Command(Type::data_manipulation),
			  _begin(std::stoi(args[0])),
			  _end(std::stoi(args[1])) {}
		~CopyCommand() {}

		Errors validate(const std::string& data, const std::string&) const override
		{
			const int size = int(data.size());
			std::stringstream ss;
			Errors errs;

			if (_begin < -size)
			{
				ss.str("");
				ss << "Invalid begin position: "
				   << _begin << " must be greater than or equal to " << -size << "!"
				   << std::endl;
				errs.push_back(Error(ss.str()));
			}

			if (_begin >= size)
			{
				ss.str("");
				ss << "Invalid begin position: "
				   << _begin << " must be less than " << size << "!"
				   << std::endl;
				errs.push_back(Error(ss.str()));
			}

			if (_end < size)
			{
				ss.str("");
				ss << "Invalid end position: "
				   << _begin << " must be greater than or equal to " << -size << "!"
				   << std::endl;
				errs.push_back(Error(ss.str()));
			}

			if (_end >= size)
			{
				ss.str("");
				ss << "Invalid end position: "
				   << _end << " must be less than " << size << "!"
				   << std::endl;
				errs.push_back(Error(ss.str()));
			}

			if (_begin > _end)
			{
				ss.str("");
				ss << "Invalid begin and end position: "
				   << _begin << " must be less than " << _end << "!"
				   << std::endl;
				errs.push_back(Error(ss.str()));
			}

			return std::move(errs);
		}

		Result execute(const std::string& data, std::string& buffer) override
		{
			Result res(data, validate(data, buffer));

			if (!res)
				return res;

			const size_t b = (_begin >= 0) ? _begin : data.size() + _begin;
			const size_t e = (_end >= 0) ? _end : data.size() + _end;
			buffer = res.data.substr(b, (e - b));

			return res;
		}

	private:
		int _begin;
		int _end;
};


// __COPY_COMMAND_H__
#endif
