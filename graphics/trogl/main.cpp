#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "tasks/task04.hpp"
#include "tasks/task05.hpp"

#include "engine.hpp"


//logger_t globalLogging = loggerGlobal(loggerLDebug, loggerDFull);
logger_t globalLogger = loggerInit(std::cout, loggerLDebug, loggerDFull);


int main(int argc, char *argv[])
{
	TaskPtr task;

	// Choose task.
//	task = new Task04TexturesFiltering();
//	task = new Task04TexturesMixingRoad();
//	task = new Task04EarthSphereUVMapping();

	task = new Task05NormalMappingEarth();

	// Show task scene in engine.
	Engine& engine = Engine::instance();
	engine.enableFPS();
//	engine.enableCameraRotation();
	engine.setRenderMode(Engine::RenderMode::POLYGONS);
	engine.setActiveScene(task->getScene());
	engine.showActiveScene();

	return 0;
}
