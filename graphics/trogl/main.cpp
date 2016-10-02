#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::DEBUG);


int main(int argc, char *argv[])
{
	Scene scene;
	StrangeCube c;
	scene.addMesh(c);

	TroglEngine engine;
	engine.setActiveScene(scene);
	engine.showScene();

	return 0;
}
