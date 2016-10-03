#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "shaders/metamorphose_shader.h"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::DEBUG);


int main(int argc, char *argv[])
{
	Camera camera;
	camera.setPosition(glm::vec3(5.0, 4.0, 2.0));

	Scene scene("Lab02", camera);
	scene.setBgColor(Color(50, 50, 50));

	StrangeCube c;
	scene.addMesh(c);

//	StrangeCube c1(0.8, Color::red);
//	c1.setPosition(glm::vec3(-2.5, 0.0, 0.0));
//	scene.addMesh(c1);

	MetamorphoseShader mprhShader;

	TroglEngine engine;
	engine.setVertextShader(mprhShader);
	engine.setActiveScene(scene);
	engine.showScene();

	return 0;
}
