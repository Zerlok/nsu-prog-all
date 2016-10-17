#include <iostream>
#include <logger.hpp>

#include "engine.hpp"

#include "shaders/metamorphose_shader.h"
#include "shaders/screwshader.hpp"

#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "meshes/megacube.hpp"
#include "meshes/cylinder.hpp"


static Logger& globalLogger = Logger::getInstance(std::cout,
												  Logger::Level::DEBUG,
												  Logger::Description::FULL);


int main(int argc, char *argv[])
{
	TroglEngine engine;

	// Setup scene.
	Camera camera;
	camera.setPosition(glm::vec3(10.0, 4.0, 5.0));
	Scene scene("Lab02", camera);
	scene.setBgColor(Color(50, 50, 50));

//	Cube c(1.0);
//	scene.addMesh(c);

	for (size_t y = 0; y < 4; ++y)
	{
		for (size_t x = 0; x < 4; ++x)
		{
			MegaCube c;
			c.setPosition(glm::vec3(x*2.1, 0.0f, y*2.1));
			scene.addMesh(c);
		}
	}

//	Cylinder cylinder;
//	scene.addMesh(cylinder);

	engine.setActiveScene(scene);

	// Setup shaders.
	MetamorphoseShader* mprhShader = new MetamorphoseShader();
	engine.setVertextShader(mprhShader);
//	ScrewShader screwShader;
//	engine.setVertextShader(screwShader);

	// Show scene.
	engine.showScene();

	return 0;
}
