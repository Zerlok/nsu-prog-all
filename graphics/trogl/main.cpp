#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::DEBUG);


int main(int argc, char *argv[])
{
	Scene scene;
	scene.setBgColor(Color(50, 50, 50));

//	Cube c(1.0, Color::red);
	StrangeCube c;
	scene.addMesh(c);

//	Cube c1(0.8, Color::red);
//	c1.setPosition(glm::vec3(0.0, 0.0, 0.0));
//	scene.addMesh(c1);

	TroglEngine engine;
	engine.setActiveScene(scene);
	engine.showScene();

	return 0;
}
