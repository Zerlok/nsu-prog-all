class AbstractCreator
{
	public:
		virtual Strategy *create() const = 0;
};


template <class S>
class StrategyCreator : public AbstractCreator
{
	public:
		virtual Strategy *create() const { return new S(); }
};


typedef std::vector<std::string> Keys;

class StrategyFactory
{
	protected:
		typedef std::map<std::string, AbstractCreator *> FactoryMap;
		
		FactoryMap _factory;
		Keys _keys_list;

	public:
		StrategyFactory() {};
		~StrategyFactory() {};

		template <class S>
		void set(const std::string& id)
		{
			// If creator exist, it will be replaced
			_keys_list.push_back(id);
			_factory[id] = new StrategyCreator<S>();
		}

		Strategy *get(const std::string& id) const
		{
			// If creator was not found, an error will occured.
			return _factory.find(id)->second->create();
		}

		const Keys& get_registered() const
		{
			return _keys_list;
		}
};