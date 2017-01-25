#ifndef __INSERT_COMMAND_H__
#define __INSERT_COMMAND_H__


#include <sstream>
#include "command.h"


class InsertCommand : public Command
{
	public:
		class Prototype;

		InsertCommand(const int& pos)
			: Command(Type::data_manipulation),
			  _pos(pos),
			  _use_buffer(true),
			  _substr() {}
		InsertCommand(const int& pos, const std::string& substr)
			: Command(Type::data_manipulation),
			  _pos(pos),
			  _use_buffer(false),
			  _substr(substr) {}
		~InsertCommand() {}

		size_t count_pos(const int& p, const std::string& data) const
		{
			const size_t& size = data.size();
			size_t pos = (size + p) % size;
			if (p < 0)
				pos += 1;

			return pos;
		}

		Errors validate(const std::string &data, const std::string &buffer) const override
		{
			Errors errs;
			const size_t size = data.size();
			const size_t pos = count_pos(_pos, data);

			if (pos > size)
			{
				std::stringstream ss;
				ss << pos << " must be less than " << size << std::endl;
				errs.push_back(Error("Insert position out of range!", ss.str()));
			}

			if (_use_buffer
					&& buffer.empty())
				errs.push_back(Error("Inserting buffer is empty!"));

			return std::move(errs);
		}

		Result execute(const std::string &data, std::string &buffer) override
		{
			Result res(data, validate(data, buffer));

			if (_use_buffer)
				_substr = buffer;

			if (res)
				res.data.insert(count_pos(_pos, data), _substr);

			return std::move(res);
		}

	private:
		int _pos;
		bool _use_buffer;
		std::string _substr;
};


class InsertCommand::Prototype : public AbstractPrototype
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
				res.errors.push_back(Error("Invalid number of arguments!", "Only one argument is required: insert_pos."));

			else
			{
				int pos;
				try
				{
					pos = std::stoi(arguments[0]);
				}
				catch (const std::invalid_argument&)
				{
					res.errors.push_back(Error(Error::type::invalid_argument_type, "Insert argument must be an integer: insert_pos."));
				}

				if (arguments.size() == 1)
					res.ptr = new InsertCommand(pos);
				else
				{
					std::stringstream ss;
					for (size_t i = 1; i < arguments.size() - 1; ++i)
						ss << ' ' << arguments[i];
					ss << arguments.back();

					res.ptr = new InsertCommand(pos, ss.str());
				}
			}

			return std::move(res);
		}
};


// __INSERT_COMMAND_H__
#endif
