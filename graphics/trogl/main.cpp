#include <iostream>
#include <logger.hpp>

#include "engine.hpp"

#include "shaders/metamorphose_shader.h"
#include "shaders/screwshader.hpp"

#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "meshes/megacube.hpp"
#include "meshes/cylinder.hpp"


static Logger& globalLogger = Logger::getInstance(std::cout, Logger::Level::DEBUG);


int main(int argc, char *argv[])
{
	TroglEngine engine;

	// Setup scene.
	Camera camera;
	camera.setPosition(glm::vec3(5.0, 4.0, 2.0));
	Scene scene("Lab02", camera);
	scene.setBgColor(Color(50, 50, 50));

	MegaCube megaCube;
	scene.addMesh(megaCube);

//	Cylinder cylinder;
//	scene.addMesh(cylinder);

	engine.setActiveScene(scene);

	// Setup shaders.
	MetamorphoseShader mprhShader;
	engine.setVertextShader(mprhShader);
//	ScrewShader screwShader;
//	engine.setVertextShader(screwShader);

	// Show scene.
	engine.showScene();

	return 0;
}
