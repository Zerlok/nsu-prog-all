#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"


/*
 * --------------- DETAILED MODE METHODS ---------------
 */

DetailedMode::DetailedMode(
		const StrategyFactory& factory,
		const std::vector<std::string>& names,
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _factory(factory), _matrix(matrix), _configs_dir(configs_dir)
{
	if (DEBUG)
	{
		std::cout
				<< DBG_HEADER
				<< "Creating the DetailedMode..."
				<< std::endl;

		std::copy(
				names.begin(),
				names.end(),
				std::ostream_iterator<std::string>(std::cout, " "));

		std::cout << std::endl;
	}

	use(names);
}


void DetailedMode::clear()
{
	_scoretable.clear();
	_strategies.clear();
	_names.clear();
}


bool DetailedMode::use(
		const std::vector<std::string>& strategy_names)
{
	if ((strategy_names.size() != 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(
			_names.begin(),
			_names.end());

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.create(
				(*it),
				_matrix,
				_configs_dir));

		_scoretable.push_back(0);
	}

	return true;
}


std::vector<std::string> DetailedMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


std::vector<std::string> DetailedMode::get_current_strategies_names() const
{
	return _names;
}


std::vector<int> DetailedMode::get_scores() const
{
	return _scoretable;
}


bool DetailedMode::is_registered(
		const std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	auto it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool DetailedMode::are_registered(
		const std::vector<std::string>& strategy_names) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	for (auto it = strategy_names.begin();
		it != strategy_names.end();
		it++)
	{
		if (std::find(
				registered_names.begin(),
				registered_names.end(),
				(*it))
			== registered_names.end())
			return false;
	}

	return true;

	// TODO: Use all_of
	// return std::all_of(
	// 		strategy_names.begin(),
	// 		strategy_names.end(),
	// 		static_cast<std::function<bool (const std::string &)> >(is_registered));
}


void DetailedMode::play(int limit)
{
	std::vector<Decision> decisions;
	std::vector<Decision> opponents_decisions;
	int len = _names.size();

	for (int step = 0; step < limit; step++)
	{
		// All strategies makes theirs decisions.
		for (auto it = _strategies.begin();
			it != _strategies.end();
			it++)
			decisions.push_back((*it)->get_decision());

		// Each strategy learns opponents' decisions.
		for (int i = 0; i < len; i++)
		{
			for (int j = 1; j < len; j++)
				opponents_decisions.push_back(decisions[(i + j) % len]);

			_strategies[i]->learn_choices(opponents_decisions);

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
				<< std::setw(20) << _names[i]
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
		const StrategyFactory& factory,
		const std::vector<std::string>& names,
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _factory(factory), _matrix(matrix), _configs_dir(configs_dir)
{
	use(names);
}


void FastMode::clear()
{
	_scoretable.clear();
	_strategies.clear();
	_names.clear();
}


bool FastMode::use(
		const std::vector<std::string>& strategy_names)
{
	if ((strategy_names.size() != 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(
			_names.begin(),
			_names.end());

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.create(
				(*it),
				_matrix,
				_configs_dir));
		_scoretable.push_back(0);
	}

	return true;
}


std::vector<std::string> FastMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


std::vector<std::string> FastMode::get_current_strategies_names() const
{
	return _names;
}


std::vector<int> FastMode::get_scores() const
{
	return _scoretable;
}


bool FastMode::is_registered(
		const std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	auto it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool FastMode::are_registered(
		const std::vector<std::string>& strategy_names) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	for (auto it = strategy_names.begin();
		it != strategy_names.end();
		it++)
	{
		if (std::find(
				registered_names.begin(),
				registered_names.end(),
				(*it))
			== registered_names.end())
			return false;
	}

	return true;
}


void FastMode::play(int limit)
{
	std::vector<Decision> decisions;
	std::vector<Decision> opponents_decisions;
	int len = _names.size();

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

			_strategies[i]->learn_choices(opponents_decisions);

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
		const StrategyFactory& factory,
		const std::vector<std::string>& names,
		const ScoreMatrix& matrix,
		const std::string& configs_dir)
	: _factory(factory), _matrix(matrix), _configs_dir(configs_dir)
{
	use(names);
}


void TournamentMode::clear()
{
	_scoretable.clear();
	_strategies.clear();
	_names.clear();
}


bool TournamentMode::use(
		const std::vector<std::string>& strategy_names)
{
	if ((strategy_names.size() < 3)
		|| (!are_registered(strategy_names)))
	{
		return false;
	}

	clear();

	_names = strategy_names;
	std::sort(
			_names.begin(),
			_names.end());

	for (auto it = _names.begin();
		it != _names.end();
		it++)
	{
		_strategies.push_back(_factory.create(
				(*it),
				_matrix,
				_configs_dir));
		_scoretable.push_back(0);
	}

	return true;
}


std::vector<std::string> TournamentMode::get_available_strategies_names() const
{
	return _factory.get_registered();
}


std::vector<std::string> TournamentMode::get_current_strategies_names() const
{
	return _names;
}


std::vector<int> TournamentMode::get_scores() const
{
	return _scoretable;
}


bool TournamentMode::is_registered(
		const std::string& strategy_name) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	auto it = std::find(
			registered_names.begin(),
			registered_names.end(),
			strategy_name);

	return (it != registered_names.end());
}


bool TournamentMode::are_registered(
		const std::vector<std::string>& strategy_names) const
{
	const std::vector<std::string>& registered_names = _factory.get_registered();

	for (auto it = strategy_names.begin();
		it != strategy_names.end();
		it++)
	{
		if (std::find(
				registered_names.begin(),
				registered_names.end(),
				(*it))
			== registered_names.end())
			return false;
	}

	return true;
}


void TournamentMode::play(int limit)
{
	std::cout << "Nah, you will not play this time :P" << std::endl;

	// std::vector<Decision> decisions;
	// std::vector<Decision> opponents_decisions;
	// int len = _names.size();

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

	// 		_strategies[i]->learn_choices(opponents_decisions);

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
