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
typedef std::vector<std::string> Keys;


class StrategyFactory
{
	public:
		StrategyFactory(
				const ScoreMatrix& matrix,
				const std::string& configs_dir)
			: _matrix(matrix), _configs_dir(configs_dir) {}

		~StrategyFactory() {}

		template <class S>
		void set_id(const std::string& id)
		{
			// If creator exist, it will be replaced
			_keys_list.push_back(id);
			_factory[id] = new StrategyCreator<S>();
		}

		Strategy *get(const std::string& id) const
		{
			// If creator was not found, an error will occured.
			return _factory.find(id)->second->create(
					_matrix,
					_configs_dir);
		}

		const Keys& get_all_registered() const
		{
			return _keys_list;
		}

	private:
		FactoryMap _factory;
		Keys _keys_list;

		const ScoreMatrix _matrix;
		const std::string _configs_dir;
};


// __FACTORY_H__
#endif
