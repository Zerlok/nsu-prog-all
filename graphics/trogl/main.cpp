#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshes/cube.hpp"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::INFO);


int main(int argc, char *argv[])
{
	Scene scene;
	scene.addMesh(Cube(1.0));

	TroglEngine engine;
	engine.showScene(scene);

	return 0;
}
