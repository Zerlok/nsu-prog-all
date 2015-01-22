#ifndef __FACTORY_H__
#define __FACTORY_H__


class AbstractCreator
{
	public:
		virtual Strategy *create(
				const ScoreMatrix& matrix,
				const std::string& configs_dir) const = 0;
};


template <class S>
class StrategyCreator : public AbstractCreator
{
	public:
		virtual Strategy *create(
				const ScoreMatrix& matrix,
				const std::string& configs_dir) const
		{
			return new S(matrix, configs_dir);
		}
};


class StrategyFactory
{
	protected:
		typedef std::map<std::string, AbstractCreator *> FactoryMap;
	
	public:
		StrategyFactory() {};

		StrategyFactory(const StrategyFactory& f) : _map(f._map) {};

		~StrategyFactory() {};

		template <class S>
		void register_id(const std::string& id)
		{
			_map[id] = new StrategyCreator<S>();
		}

		Strategy *create(
				const std::string& id,
				const ScoreMatrix& matrix,
				const std::string& configs_dir) const
		{
			// If creator was not found, an error will occured.
			return _map.find(id)->second->create(
					matrix,
					configs_dir);
		}

		const std::vector<std::string> get_registered() const
		{
			std::vector<std::string> keys;

			for (auto it = _map.begin();
				it != _map.end();
				it++)
				keys.push_back(it->first);

			return keys;
		}

	private:
		FactoryMap _map;
};


// __FACTORY_H__
#endif
