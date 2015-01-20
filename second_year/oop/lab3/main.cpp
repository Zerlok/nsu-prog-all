#include "main.h"

#include "strategy.h"
#include "factory.h"
// #include "mode.h"
// #include "game.h"


// int main(const int argc, const char **argv)
// {
// 	Game prisoners_game(argc, argv);

// 	prisoners_game.run();

// 	return 0;
// }


const ScoreMatrix get_default_matrix()
{
	std::map< std::vector<Decision>, std::vector<int> > m;

    m[{cooperate, cooperate, cooperate}] = {4, 4, 4};
    m[{cooperate, cooperate, defect   }] = {2, 2, 5};
    m[{cooperate, defect,    cooperate}] = {2, 5, 2};
    m[{cooperate, defect,    defect   }] = {0, 3, 3};
    m[{defect,    cooperate, cooperate}] = {5, 2, 2};
    m[{defect,    cooperate, defect   }] = {3, 0, 3};
    m[{defect,    defect,    cooperate}] = {3, 3, 0};
    m[{defect,    defect,    defect   }] = {1, 1, 1};

	return m;
}


void show_matrix(const ScoreMatrix& matrix)
{
	for (ScoreMatrix::const_iterator it = matrix.begin();
		it != matrix.end();
		it++)
	{
		std::copy(
				(*it).first.begin(),
				(*it).first.end(),
				std::ostream_iterator<int>(std::cout, " ")
		);

		std::cout << " => ";

		std::copy(
				(*it).second.begin(),
				(*it).second.end(),
				std::ostream_iterator<int>(std::cout, " ")
		);

		std::cout << std::endl;
	}
}


int main(const int argc, const char **argv)
{
	const ScoreMatrix matrix = get_default_matrix();

	StrategyFactory f(matrix, "");

	f.set_id<TrustfulStrategy>("trust");
	f.set_id<MistrustfulStrategy>("mistrust");
	f.set_id<CrazyStrategy>("crazy");

	std::vector<Strategy *> strategies;
	std::vector<Decision> decisions;
	std::vector<int> current_scores, total_scores = {0, 0, 0};

	strategies.push_back(f.get("crazy"));
	strategies.push_back(f.get("trust"));
	strategies.push_back(f.get("mistrust"));

	for (auto it = strategies.begin();
		it != strategies.end();
		it++)
	{
		decisions.push_back((*it)->get_decision());
	}

	current_scores = matrix.at(decisions);

	auto cur = current_scores.begin();
	for (auto it = total_scores.begin();
		it != total_scores.end();
		it++)
	{
		(*it) += (*cur);
		cur++;
	}

	std::copy(
			total_scores.begin(),
			total_scores.end(),
			std::ostream_iterator<int>(std::cout, ", ")
	);

	return 0;
}