#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "shaders/metamorphose_shader.h"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::DEBUG);


int main(int argc, char *argv[])
{
	TroglEngine engine;

	// Setup scene.
	Camera camera;
	camera.setPosition(glm::vec3(5.0, 4.0, 2.0));
	Scene scene("Lab02", camera);
	scene.setBgColor(Color(50, 50, 50));

	StrangeCube c;
	scene.addMesh(c);

	engine.setActiveScene(scene);

	// Setup shaders.
	MetamorphoseShader mprhShader;
	engine.setVertextShader(mprhShader);

	// Show scene.
	engine.showScene();

	return 0;
}
