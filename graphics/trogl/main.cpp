#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "engine.hpp"

#include "common/utils.h"
#include "common/color.hpp"
#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "meshes/megacube.hpp"
#include "meshes/cylinder.hpp"


logger_t loggerGlobalInstance = logger_i(
		std::cout,
		logger_l::DEBUG,
		logger_d::FULL
);


int main(int argc, char *argv[])
{
	const int size = 3;
	const float offset = 2.5;
	const glm::vec3 cameraPos = glm::vec3(
			2*(size+1)*offset,
			(size+1)*offset / 1.8,
			(size+1)*offset
	);

	Engine engine;

	// Setup scene.
	CameraPtr camera = new Camera();
	camera->setPosition(cameraPos);
	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);

	const double start = getTimeDouble();
	for (int z = -size; z < size+1; ++z)
	{
		for (int y = -size; y < size+1; ++y)
		{
			for (int x = -size; x < size+1; ++x)
			{
				MeshPtr c = new MegaCube(Color::black, Color::white);
				c->setPosition(glm::vec3(x*offset, y*offset, z*offset));
				scene->addMesh(c);
			}
		}
	}
	const double end = getTimeDouble();
	logInfo << std::pow(2*size + 1, 3) << " meshes created (duration: "
			<< std::setprecision(9) << (end - start) << "s)" << logEndl;

	// Show scene.
	engine.setActiveScene(scene);
	engine.setDisplayFPS(true);
	engine.showScene();

	return 0;
}
