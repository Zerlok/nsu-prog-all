#include "main.h"


class Strategy
{
	public:
		virtual ~Strategy() {}
		virtual void make_decision() = 0;
};


class AbstractCreator
{
	public:
		virtual Strategy *create() const = 0;
};


template <class S>
class StrategyCreator : public AbstractCreator
{
	public:
		virtual Strategy *create() const
		{
			return new S();
		}
};


class StrategyFactory
{
	protected:
		typedef std::map<std::string, *AbstractCreator> FactoryMap;
		FactoryMap _factory;

	public:
		StrategyFactory();
		~StrategyFactory();

		template <class S>
		void push(const std::string& id)
		{
			// If creator exist -> it will be replaced
			_factory[id] = new StrategyCreator<S>();
		}

		Strategy *get(const std::string & id)
		{
			// If creator was not found -> an error will occured.
			return _factory.find(id)->second->create();
		}
};
