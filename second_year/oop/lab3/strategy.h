#ifndef __STRATEGY_H__
#define __STRATEGY_H__


class Strategy
{
	public:
		Strategy(
				// const std::array<MatrixField, 8>& matrix,
				// const std::string& configs_dir
		) {}

		virtual ~Strategy() {}

		virtual Decision get_decision() = 0;
		virtual void learn_choices(
				// const std::array<Decision, 2>& decisions
				const Decision *decisions
		) = 0;
};


class TrustfulStrategy : public Strategy
{
	public:
		TrustfulStrategy(
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix = NULL,
				const std::string& configs_dir = "")
			: _matrix(matrix), _configs_dir(configs_dir)
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

		~TrustfulStrategy() {}

		virtual Decision get_decision() { return cooperate; }
		virtual void learn_choices(
				// const std::array<Decision, 2>& decisions
				const Decision *decisions
		) {}
	
	private:
		// const std::array<MatrixField, 8> _matrix;
		const MatrixField **_matrix;
		const std::string _configs_dir;
};


class MistrustfulStrategy : public Strategy
{
	public:
		MistrustfulStrategy(
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix = NULL,
				const std::string& configs_dir = "")
			: _matrix(matrix), _configs_dir(configs_dir)
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

		~MistrustfulStrategy() {}

		virtual Decision get_decision() { return defect; }
		virtual void learn_choices(
				// const std::array<Decision, 2>& decisions
				const Decision *decisions
		) {}

	private:
		// const std::array<MatrixField, 8> _matrix;
		const MatrixField **_matrix;
		const std::string _configs_dir;
};


class CrazyStrategy : public Strategy
{
	public:
		CrazyStrategy(
				// const std::array<MatrixField, 8>& matrix,
				const MatrixField **matrix = NULL,
				const std::string& configs_dir = "")
			: _matrix(matrix), _configs_dir(configs_dir)
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

		~CrazyStrategy() {}

		virtual Decision get_decision()
		{
			srand(time(NULL));

			return (rand() % 2) ? cooperate : defect;
		}

		virtual void learn_choices(
				// const std::array<Decision, 2>& decisions
				const Decision *decisions
		) {}

	private:
		// const std::array<MatrixField, 8> _matrix;
		const MatrixField **_matrix;
		const std::string _configs_dir;
};


// __STRATEGY_H__
#endif