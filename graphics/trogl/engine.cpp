#include "engine.hpp"

#include <logger.hpp>


TroglEngine::TroglEngine()
{
	logDebug << "Engine created" << logEnd;
}


TroglEngine::~TroglEngine()
{
	logDebug << "Engine removed" << logEnd;
}


void TroglEngine::showScene(const Scene& scene)
{
	logDebug << "Engine scene rendering started" << logEnd;
	// TODO: add scene lamps.
	// TODO: add scene meshes.
}
