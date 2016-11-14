#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "common/utils.hpp"
#include "common/color.hpp"

#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "meshes/megacube.hpp"
#include "meshes/cylinder.hpp"
#include "meshes/sphere.hpp"
#include "meshes/plane.hpp"

#include "materials/diffusematerial.hpp"
#include "shaders/diffuseshader.hpp"

#include "engine.hpp"
#include "engineutils.hpp"


logger_t globalLogger = loggerInit(std::cout, Logger::Level::DEBUG, loggerDescriptionFull);


int main(int argc, char *argv[])
{
	// Meshes generation settings.
	const size_t size = 5;
	const float offset = 2.5;
	const glm::vec3 direction {0.0, 0.0, 1.0};
	const glm::vec3 cameraPos {(size)*offset, (size)*offset / 1.8, (size)*offset};

	// Mesh settings.
//	using MyMesh = Cube;
//	const MyMesh clonableMesh = Cube(4.0, Color::red);
//	using MyMesh = MegaCube;
//	const MyMesh clonableMesh = MegaCube(Color::white, Color::black);
	using MyMesh = Sphere;
	MyMesh clonableMesh = MyMesh(1.0, 11);
	using MeshGenerator = ObjectGenerator<MyMesh, ObjectGeneratorTraits<Mesh> >;

	// Setup scene.
	CameraPtr camera = new Camera();
	camera->setPosition(cameraPos);
	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);

	// Generate meshes.
	MeshPtr floor = new Plane(Color(100, 200, 100));
	floor->setScale({30.0, 0.0, 30.0});
	floor->setPosition({0.0, -2.0, 0.0});
	scene->addMesh(floor);

	MeshGenerator meshGenerator;
//	const MeshGenerator::Objects meshes = meshGenerator.latticeArrangement(size, offset, clonableMesh);
	const MeshGenerator::Objects meshes = meshGenerator.directionArrangement(size, offset, direction, clonableMesh);
	for (const MeshGenerator::ObjectPointer& m : meshes)
		scene->addMesh(m);

	// Add light.
	LightPtr lamp = new Light(Light::createPoint());
//	LightPtr lamp = new Light(Light::createSun());
//	LightPtr lamp = new Light(Light::createSpot());
//	LightPtr lamp = scene->getAmbientLight();
	scene->addLight(lamp);

	// Show scene.
	Engine& engine = Engine::instance();
	engine.enableFPS();
//	engine.setRenderMode(Engine::RenderMode::EDGES);
	engine.setActiveScene(scene);
	engine.showActiveScene();

	return 0;
}
