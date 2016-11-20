#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "common/utils.hpp"
#include "common/color.hpp"

#include "shaders/diffuseshader.hpp"
#include "materials/diffusematerial.hpp"

#include "meshes/sphere.hpp"
#include "meshes/plane.hpp"

#include "engine.hpp"
#include "engineutils.hpp"


logger_t globalLogging = loggerGlobal(loggerLDebug, loggerDFull);
logger_t globalLogger = loggerInit(std::cout, loggerLDebug, loggerDFull);


int main(int argc, char *argv[])
{
	// Some mesh generation attributes.
	const size_t size = 5;
	const float offset = 2.5;
	const glm::vec3 direction {0.0, 0.0, 1.0};
	const glm::vec3 cameraPos {(size)*offset, (size)*offset / 1.8, (size)*offset};

	// Setup scene.
	CameraPtr camera = new Camera();
	camera->setPosition(cameraPos);

	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);
	scene->setAmbient(0.7);

	// Add floor to the scene.
	MaterialPtr floorMat = new DiffuseMaterial(Color(120, 200, 120), 1.0, 0.2, 2.0);
	MeshPtr floor = new Plane();
	floor->setMaterial(floorMat);
	floor->setPosition({0.0, -2.0, 0.0});
	floor->setScale({30.0, 0.0, 30.0});
	scene->addMesh(floor);

	// Add meshes to the scene.
	MaterialPtr spheresMat = new DiffuseMaterial(Color(250, 100, 100), 1.0, 0.7);
	Sphere baseSphere = Sphere(1.0, 11);
	baseSphere.setMaterial(spheresMat);

	using MeshGenerator = ObjectGenerator<Sphere, ObjectGeneratorTraits<Mesh> >;
	MeshGenerator meshGenerator;
//	const MeshGenerator::Objects meshes = meshGenerator.latticeArrangement(size, offset, baseSphere);
	const MeshGenerator::Objects meshes = meshGenerator.directionArrangement(size, offset, direction, baseSphere);
	for (const MeshGenerator::ObjectPointer& m : meshes)
		scene->addMesh(m);

	// Add light to the scene.
	LightPtr lamp = new Light(Light::createPoint());
//	LightPtr lamp = new Light(Light::createSun());
//	LightPtr lamp = new Light(Light::createSpot());
//	LightPtr lamp = scene->getAmbientLight();
//	lamp->setColor({200, 200, 255});
	scene->addLight(lamp);

	// Show scene.
	Engine& engine = Engine::instance();
	engine.enableFPS();
	engine.setRenderMode(Engine::RenderMode::POLYGONS);
	engine.setActiveScene(scene);
	engine.showActiveScene();

	return 0;
}
