#include "main.h"


/*
 * --------------- DETAILED MODE METHODS ---------------
 */

DetailedMode::DetailedMode()
{
	_strategy_0 = NULL;
	_strategy_1 = NULL;
	_strategy_2 = NULL;
}


DetailedMode::~DetailedMode()
{
	delete _strategy_0;
	delete _strategy_1;
	delete _strategy_2;
}


void DetailedMode::setup(
		Strategy *s0,
		Strategy *s1,
		Strategy *s2)
{
	delete _strategy_0;
	delete _strategy_1;
	delete _strategy_2;
	
	_strategy_0 = s0;
	_strategy_1 = s1;
	_strategy_2 = s2;
}


void DetailedMode::play()
{
	Decision decision_list[3] = {
			_strategy_0->get_decision(),
			_strategy_1->get_decision(),
			_strategy_2->get_decision()
	};

	_strategy_0->learn_choices(0, decision_list);
	_strategy_1->learn_choices(1, decision_list);
	_strategy_2->learn_choices(2, decision_list);

	std::cout
			<< decision_list[0]
			<< decision_list[1]
			<< decision_list[2]
			<< std::endl;
}


/*
 * --------------- FAST MODE METHODS ---------------
 */

FastMode::FastMode()
{

}


FastMode::~FastMode()
{

}


void FastMode::play()
{
	std::cout << "Playing a fast mode..." << std::endl;
}


/*
 * --------------- TOURNAMENT MODE METHODS ---------------
 */

TournamentMode::TournamentMode()
{

}


TournamentMode::~TournamentMode()
{

}


void TournamentMode::play()
{
	std::cout << "Playing a tournament mode..." << std::endl;
}
