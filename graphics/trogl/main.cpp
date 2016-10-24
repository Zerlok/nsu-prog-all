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


loggerType loggerGlobalInstance = loggerInit(std::cout,
											 Logger::Level::INFO,
											 Logger::Description::FULL);


template<class M>
void fillSceneWithMeshes(ScenePtr& scene, const size_t& size)
{
	int sizeInt = size;
	size_t verticesNum = 0;
	size_t facesNum = 0;

	const float offset = 2.5;
	const glm::vec3 cameraPos = glm::vec3(
			2*(size+1)*offset,
			(size+1)*offset / 1.8,
			(size+1)*offset
	);
	CameraPtr& camera = scene->getCamera();
	camera->setPosition(cameraPos);

	const double start = getTimeDouble();
	for (int z = -sizeInt; z < sizeInt+1; ++z)
	{
		for (int y = -sizeInt; y < sizeInt+1; ++y)
		{
			for (int x = -sizeInt; x < sizeInt+1; ++x)
			{
				MeshPtr c = new M(Color::black, Color::white);
				c->setPosition(glm::vec3(x*offset, y*offset, z*offset));
				scene->addMesh(c);

				verticesNum += c->getVertices().size();
				facesNum += c->getFaces().size();
			}
		}
	}
	const double end = getTimeDouble();
	logInfo << std::pow(2*sizeInt + 1, 3) << " meshes created"
			<< " (vertices: " << verticesNum << ", faces: " << facesNum
			<< ") (duration: " << std::setprecision(9) << (end - start) << "s)" << logEndl;
}


int main(int argc, char *argv[])
{
	Engine engine;

	// Setup scene.
	CameraPtr camera = new Camera();
	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);

	fillSceneWithMeshes<Cylinder>(scene, 3);

	// Show scene.
	engine.setActiveScene(scene);
	engine.setDisplayFPS(true);
	engine.showScene();

	return 0;
}
