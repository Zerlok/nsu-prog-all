#ifndef __COPY_COMMAND_H__
#define __COPY_COMMAND_H__


#include <string>
#include <sstream>
#include "command.h"


class CopyCommand : public Command
{
	public:
		class Prototype;

		CopyCommand(const int& begin = 0, const int& end = -1)
			: Command(Type::data_manipulation),
			  _begin(begin),
			  _end(end) {}
		~CopyCommand() {}

		size_t count_pos(const int& p, const std::string& data) const
		{
			const size_t& size = data.size();
			size_t pos = (size + p) % size;
			if (p < 0)
				pos += 1;

			return pos;
		}

		Errors validate(const std::string& data, const std::string&) const override
		{
			std::stringstream ss;
			Errors errs;
			const size_t size = data.size();

			if (size == 0)
			{
				errs.push_back(Error("Data is empty", ss.str()));
				return std::move(errs);
			}

			const size_t b = count_pos(_begin, data);
			const size_t e = count_pos(_end, data);

			if (b >= size)
			{
				ss.str("");
				ss << "Invalid begin position: "
				   << b << " must less than " << size << "!"
				   << std::endl;
				errs.push_back(Error("Invalid copy range", ss.str()));
			}

			if (e > size)
			{
				ss.str("");
				ss << "Invalid end position: "
				   << e << " must be less than " << size << "!"
				   << std::endl;
				errs.push_back(Error("Invalid copy range", ss.str()));
			}

			if (b > e)
			{
				ss.str("");
				ss << "Invalid begin and end position: "
				   << b << " must be less than " << e << "!"
				   << std::endl;
				errs.push_back(Error("Invalid copy range", ss.str()));
			}

			return std::move(errs);
		}

		Result execute(const std::string& data, std::string& buffer) override
		{
			Result res(data, validate(data, buffer));

			if (!res)
				return res;

			const size_t b = count_pos(_begin, data);
			const size_t e = count_pos(_end, data);
			buffer = res.data.substr(b, (e - b));

			return res;
		}

	private:
		int _begin;
		int _end;
};

class CopyCommand::Prototype : public AbstractPrototype
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

		if (arguments.empty())
			res.ptr = new CopyCommand();

		else if (arguments.size() != 2)
			res.errors.push_back(Error(Error::type::invalid_arguments_num, "Only 2 arguments required: start_pos, end_pos"));

		else // valid number of arguments received.
		{
			int b;
			int e;

			try
			{
				b = std::stoi(arguments[0]);
			}
			catch (const std::invalid_argument&)
			{
				res.errors.push_back(Error(Error::type::invalid_argument_type, "Copy begin position must be an integer!"));
			}

			try
			{
				e = std::stoi(arguments[1]);
			}
			catch (const std::invalid_argument&)
			{
				res.errors.push_back(Error(Error::type::invalid_argument_type, "Copy end position must be an integer!"));
			}

			if (res)
				res.ptr = new CopyCommand(b, e);
		}

		return std::move(res);
	}
};


// __COPY_COMMAND_H__
#endif
