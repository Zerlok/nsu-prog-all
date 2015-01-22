#include "main.h"

#include "strategy.h"
#include "factory.h"


template <class S>
Strategy *StrategyCreator<S>::create(
		const ScoreMatrix& matrix,
		const std::string& configs_dir) const
{
	return new S(matrix, configs_dir);
}


StrategyFactory::StrategyFactory(
		const StrategyFactory& f)
	: _map(f._map) {}


// TODO: Replace the function declaration from header.

template <class S>
void StrategyFactory::register_id(const std::string& id)
{
	_map[id] = new StrategyCreator<S>();
}


Strategy *StrategyFactory::create(
		const std::string& id,
		const ScoreMatrix& matrix,
		const std::string& configs_dir) const
{
	// If creator was not found, an error will occured.
	return _map.find(id)->second->create(
			matrix,
			configs_dir);
}


const std::vector<std::string> StrategyFactory::get_registered() const
{
	std::vector<std::string> keys;

	for (auto it = _map.begin();
		it != _map.end();
		it++)
		keys.push_back(it->first);

	return keys;
}