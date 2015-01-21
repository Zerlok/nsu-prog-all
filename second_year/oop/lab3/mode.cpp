#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"


/*
 * --------------- DETAILED MODE METHODS ---------------
 */

DetailedMode::DetailedMode(
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _matrix(matrix)
{
	StrategyFactory(matrix, configs_dir) _factory;

	clear();
}


void DetailedMode::clear()
{
	_scoretable = {0, 0, 0};
	_strategies.clear();
	_names.clear();
}


bool DetailedMode::use(std::vector<std::string>& strategy_names)
{
	if ((strategy_names.length() != 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(_names);

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.get((*it)));
		_scoretable.push_back(0);
	}

	return true;
}


const std::vector<std::string> DetailedMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


const std::vector<std::string> DetailedMode::get_current_strategies_names() const
{
	return _names;
}


const std::vector<int> DetailedMode::get_scores() const
{
	return _scoretable;
}


bool DetailedMode::is_registered(
		std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool DetailedMode::are_registered(
		std::vector<std::string>& strategy_names) const
{
	return std::all_of(
			strategy_names.begin(),
			strategy_names.end(),
			is_registered());
}


void DetailedMode::play(int limit)
{
	std::vector<Decision> decisions;
	std::vector<Decision> opponents_decisions;
	int len = _names.length();

	for (int step = 0; step < limit; step++)
	{
		// All strategies makes theirs decisions.
		for (auto it = _strategies.begin();
			it != _strategies.end();
			it++)
		{
			decisions.push_back(
					(*it)->get_decision()
			);
		}

		// Each strategy learns opponents' decisions.
		for (int i = 0; i < len; i++)
		{
			for (int j = 1; j < len; j++)
				opponents_decisions.push_back(decisions[(i + j) % len]);

			_strategies[i]->learn_decisions(opponents_decisions);

			opponents_decisions.clear();
		}

		// Mode counts scores by using the game matrix.
		std::vector<int> current_scores = _matrix.at(decisions);
		auto cur = current_scores.begin();

		// Mode applies new scores to the scoretable.
		for (auto it = _scoretable.begin();
			it != _scoretable.end();
			it++)
		{
			(*it) += (*cur);
			cur++;
		}

		// This mode shows strategies' decisions in each step.
		std::cout
				<< std::setw(20) << "Name"
				<< std::setw(20) << ": Decision"
				<< std::setw(20) << ": Score"
				// << std::setw(20) << ": Total score"
				<<std::endl;

		for (int i = 0; i < len; i++) std::cout
				<< std::setw(20) << _name[i]
				<< std::setw(20) << ": " << decisions[i]
				<< std::setw(20) << ": " << current_scores[i]
				// << std::setw(20) << ": " << _scoretable[i]
				<< std::endl;
	}
}


/*
 * --------------- FAST MODE METHODS ---------------
 */

FastMode::FastMode(
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _matrix(matrix)
{
	clear();

	_factory = new StrategyFactory(matrix, configs_dir);
}


void FastMode::clear()
{
	_scoretable.clear();
	_strategies.clear();
}


bool FastMode::use(std::vector<std::string>& strategy_names)
{
	if ((strategy_names.length() != 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(_names);

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.get((*it)));
		_scoretable.push_back(0);
	}

	return true;
}


const std::vector<std::string> FastMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


const std::vector<std::string> FastMode::get_current_strategies_names() const
{
	return _names;
}


const std::vector<int> FastMode::get_scores() const
{
	return _scoretable;
}


bool FastMode::is_registered(
		std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool FastMode::are_registered(
		std::vector<std::string>& strategy_names) const
{
	return std::all_of(
			strategy_names.begin(),
			strategy_names.end(),
			is_registered());
}


void FastMode::play(int limit)
{
	std::vector<Decision> decisions;
	std::vector<Decision> opponents_decisions;
	int len = _names.length();

	for (int step = 0; step < limit; step++)
	{
		// All strategies makes theirs decisions.
		for (auto it = _strategies.begin();
			it != _strategies.end();
			it++)
		{
			decisions.push_back(
					(*it)->get_decision()
			);
		}

		// Each strategy learns opponents' decisions.
		for (int i = 0; i < len; i++)
		{
			for (int j = 1; j < len; j++)
				opponents_decisions.push_back(decisions[(i + j) % len]);

			_strategies[i]->learn_decisions(opponents_decisions);

			opponents_decisions.clear();
		}

		// Mode counts scores by using the game matrix.
		std::vector<int> current_scores = _matrix.at(decisions);
		auto cur = current_scores.begin();

		// Mode applies new scores to the scoretable.
		for (auto it = _scoretable.begin();
			it != _scoretable.end();
			it++)
		{
			(*it) += (*cur);
			cur++;
		}
	}
}


/*
 * --------------- TOURNAMENT MODE METHODS ---------------
 */

TournamentMode::TournamentMode(
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _matrix(matrix)
{
	clear();

	_factory = new StrategyFactory(matrix, configs_dir);
}


void TournamentMode::clear()
{
	_scoretable.clear();
	_strategies.clear();
}


void TournamentMode::use(std::vector<std::string>& strategy_names)
{
	if ((strategy_names.length() < 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(_names);

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.get((*it)));
		_scoretable.push_back(0);
	}

	return true;
}


const std::vector<std::string> TournamentMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


const std::vector<std::string> TournamentMode::get_current_strategies_names() const
{
	return _names;
}


const std::vector<int> TournamentMode::get_scores() const
{
	return _scoretable;
}


bool TournamentMode::is_registered(
		std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool TournamentMode::are_registered(
		std::vector<std::string>& strategy_names) const
{
	return std::all_of(
			strategy_names.begin(),
			strategy_names.end(),
			is_registered());
}


void TournamentMode::play(int limit)
{
	std::cout << "Nah, you will not play this time :P" << std::endl;

	// std::vector<Decision> decisions;
	// std::vector<Decision> opponents_decisions;
	// int len = _names.length();

	// for (int step = 0; step < limit; step++)
	// {
	// 	// All strategies makes theirs decisions.
	// 	for (auto it = _strategies.begin();
	// 		it != _strategies.end();
	// 		it++)
	// 	{
	// 		decisions.push_back(
	// 				(*it)->get_decision()
	// 		);
	// 	}

	// 	// Each strategy learns opponents' decisions.
	// 	for (int i = 0; i < len; i++)
	// 	{
	// 		for (int j = 1; j < len; j++)
	// 			opponents_decisions.push_back(decisions[(i + j) % len]);

	// 		_strategies[i]->learn_decisions(opponents_decisions);

	// 		opponents_decisions.clear();
	// 	}

	// 	// Mode counts scores by using the game matrix.
	// 	std::vector<int> current_scores = _matrix.at(decisions);
	// 	auto cur = current_scores.begin();

	// 	// Mode applies new scores to the scoretable.
	// 	for (auto it = _scoretable.begin();
	// 		it != _scoretable.end();
	// 		it++)
	// 	{
	// 		(*it) += (*cur);
	// 		cur++;
	// 	}
	// }
}
