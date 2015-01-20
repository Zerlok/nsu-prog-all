#ifndef __FACTORY_H__
#define __FACTORY_H__


class AbstractCreator
{
	public:
		virtual Strategy *create(
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix,
				const std::string& configs_dir) const = 0;
};


template <class S>
class StrategyCreator : public AbstractCreator
{
	public:
		virtual Strategy *create(
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix,
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
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix,
				const std::string& configs_dir) : _matrix(matrix), _configs_dir(configs_dir)
		{
			// _matrix = new MatrixField[8];

			// for (int i = 0; i < 8; i++)
			// {
			// 	_matrix[i].decisions = new Decision[3];
			// 	_matrix[i].scores = new int[3];

			// 	for (int j = 0; j < 3; j++)
			// 	{
			// 		_matrix[i].decisions[j] = matrix[i].decisions[j];
			// 		_matrix[i].scores[j] = matrix[i].scores[j];
			// 	}
			// }
		}

		~StrategyFactory()
		{
			delete[] _matrix;
		}

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

		const MatrixField **_matrix;
		const std::string _configs_dir;
		
		// const std::array<MatrixField, 8> _matrix;
};


// __FACTORY_H__
#endif
