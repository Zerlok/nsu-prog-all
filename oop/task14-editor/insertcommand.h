#ifndef __INSERT_COMMAND_H__
#define __INSERT_COMMAND_H__


#include <sstream>
#include "command.h"


class InsertCommand : public Command
{
	public:
		InsertCommand(const int& pos)
			: Command(Type::data_manipulation),
			  _pos(pos) {}
		InsertCommand(const Strings& args)
			: Command(Type::data_manipulation),
			  _pos(std::stoi(args[0])) {}
		~InsertCommand() {}

		Errors validate(const std::string &data, const std::string &buffer) const override
		{
			std::stringstream ss;
			Errors errs;
			const int size = data.size();

			if (_pos < -size)
			{
				ss << _pos << " must be greater than or equal to " << -size << std::endl;
				errs.push_back(Error("Insert position out of range!", ss.str()));
				ss.str("");
			}

			if (size <= _pos)
			{
				ss << _pos << " must be less than " << size << std::endl;
				errs.push_back(Error("Insert position out of range!", ss.str()));
				ss.str("");
			}

			if (buffer.empty())
				errs.push_back(Error("Inserting buffer is empty!"));

			return std::move(errs);
		}

		Result execute(const std::string &data, std::string &buffer) override
		{
			Result res(data, validate(data, buffer));

			if (!res)
				return std::move(res);

			res.data.insert(_pos, buffer);

			return std::move(res);
		}

	private:
		int _pos;
};


// __INSERT_COMMAND_H__
#endif
