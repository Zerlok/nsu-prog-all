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

#include "materials/diffusematerial.hpp"
#include "shaders/diffuseshader.hpp"

#include "engine.hpp"
#include "engineutils.hpp"


logger_t globalLogger = loggerInit(std::cout, Logger::Level::DEBUG, loggerDescriptionFull);


int main(int argc, char *argv[])
{
	// Meshes generation settings.
	const size_t size = 3;
	const float offset = 2.5;
	const glm::vec3 direction {0.0, 0.0, 1.0};
	const glm::vec3 cameraPos {(size)*offset, (size)*offset / 1.8, (size)*offset};

	// Mesh settings.
//	using MyMesh = Cube;
//	const MyMesh clonableMesh = Cube(4.0, Color::red);
//	using MyMesh = MegaCube;
//	const MyMesh clonableMesh = MegaCube(Color::white, Color::black);
	using MyMesh = Sphere;
	MyMesh clonableMesh = MyMesh(2.0, 11);
	using MeshGenerator = ObjectGenerator<MyMesh, ObjectGeneratorTraits<Mesh> >;

	// Setup scene.
	CameraPtr camera = new Camera();
	camera->setPosition(cameraPos);
	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);

	// Generate meshes.
	MeshGenerator meshGenerator;
//	const MeshGenerator::Objects meshes = meshGenerator.latticeArrangement(size, offset, clonableMesh);
	const MeshGenerator::Objects meshes = meshGenerator.directionArrangement(size, offset, direction, clonableMesh);
	for (const MeshGenerator::ObjectPointer& m : meshes)
		scene->addMesh(m);

	// Add light.	
//	LightPtr lamp = new Light(Light::Type::POINT);
//	lamp->setPower(1000.0);
	LightPtr lamp = new Light(Light::Type::SUN);
	lamp->setPower(1.0);
//	LightPtr lamp = scene->getAmbientLight();
	lamp->setPosition({0.0, 30.0, 0.0});
	scene->addLight(lamp);

	// Show scene.
	Engine& engine = Engine::instance();
	engine.enableFPS();
	engine.setRenderMode(Engine::RenderMode::POLYGONS);
	engine.setActiveScene(scene);
	engine.validate();
	engine.showScene();

	return 0;
}
