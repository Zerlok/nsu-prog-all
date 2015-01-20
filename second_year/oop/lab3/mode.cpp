#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"


/*
 * --------------- DETAILED MODE METHODS ---------------
 */

DetailedMode::DetailedMode(
		const MatrixField **matrix,
		const std::string& configs_dir)
	// : _matrix(matrix), _configs_dir(configs_dir)
{
	_factory = new StrategyFactory(matrix, configs_dir);
	_strategies = NULL;
}


DetailedMode::~DetailedMode() {}


void DetailedMode::play()
{
	// std::vector<Decision> decisions;

	// for (std::vector<Strategy *>::iterator item = _strategies->begin(); item != _strategies->end(); item++)
	// 	decisions.push_back(
	// 			(*item)->get_decision()
	// 	);

	// for (int i = 0; std::vector<Strategy *>::iterator item = _strategies.begin(); item != _strategies.end(); i++; item++)
	// 	(*item)->learn_choices(i, decisions);
	
	Decision opponents[2];
	Decision decisions[3];

	for (int i = 0; i < 3; i++)
		decisions[i] = _strategies[i]->get_decision();

	for (int i = 0; i < 3; i++)
	{
		opponents[0] = decisions[(i + 1) % 3];
		opponents[1] = decisions[(i + 2) % 3];

		_strategies[i]->learn_choices(opponents);
	}

	std::cout
			<< decisions[0] << "\n"
			<< decisions[1] << "\n"
			<< decisions[2] << "\n";
}


/*
 * --------------- FAST MODE METHODS ---------------
 */

FastMode::FastMode(
		const MatrixField **matrix,
		const std::string& configs_dir)
{
	_factory = new StrategyFactory(matrix, configs_dir);
	_strategies = NULL;
}


FastMode::~FastMode() {}


void FastMode::play()
{
	std::cout << "Playing a fast mode..." << std::endl;
}


/*
 * --------------- TOURNAMENT MODE METHODS ---------------
 */

TournamentMode::TournamentMode(
		const MatrixField **matrix,
		const std::string& configs_dir)
{
	_factory = new StrategyFactory(matrix, configs_dir);
	_strategies = NULL;
}


TournamentMode::~TournamentMode() {}


void TournamentMode::play()
{
	std::cout << "Playing a tournament mode..." << std::endl;
}
