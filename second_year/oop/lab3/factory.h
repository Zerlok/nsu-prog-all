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


typedef std::map<std::string, AbstractCreator *> FactoryMap;


class StrategyFactory
{
	public:
		StrategyFactory(
				const ScoreMatrix& matrix,
				const std::string& configs_dir)
			: _matrix(matrix), _configs_dir(configs_dir)
		{
			time_t t;
			time(&t);
			
			srand((unsigned int) t);
		}

		~StrategyFactory() {}

		template <class S>
		void set_id(const std::string& id)
		{
			// If creator exist, it will be replaced
			_map[id] = new StrategyCreator<S>();
		}

		Strategy *get(const std::string& id) const
		{
			// If creator was not found, an error will occured.
			return _map.find(id)->second->create(
					_matrix,
					_configs_dir);
		}

		const Keys& get_registered() const
		{
			std::vector<std::string> keys;

			for (auto it = _map.begin();
				it != map.end();
				it++)
			{
				keys.push_back(it->first);
			}
		}

	private:
		FactoryMap _map;
		Keys _keys_list;

		const ScoreMatrix _matrix;
		const std::string _configs_dir;
};


// __FACTORY_H__
#endif
