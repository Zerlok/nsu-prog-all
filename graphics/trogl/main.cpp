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
	const size_t size = 1;
	const float offset = 2.5;
	const glm::vec3 cameraPos = glm::vec3(2*(size)*offset,
										  (size)*offset / 1.8,
										  (size)*offset);

	using MyMesh = Cube;
	const MyMesh clonableMesh = Cube();
//	using MyMesh = MegaCube;
//	const MyMesh clonableMesh = MegaCube(Color::white, Color::black);
//	using MyMesh = Sphere;
//	MyMesh clonableMesh = MyMesh(4.0, 8, 16);
	using MeshGenerator = ObjectGenerator<MyMesh, ObjectGeneratorTraits<Mesh> >;

	// Setup scene.
	CameraPtr camera = new Camera();
	camera->setPosition(cameraPos);
	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);

	// Generate meshes.
	MeshGenerator meshGenerator;
	const MeshGenerator::Objects meshes = meshGenerator.cloneObjectsWithLatticeArrangement(size, offset, clonableMesh);
	for (const MeshGenerator::ObjectPointer& m : meshes)
		scene->addMesh(m);

	// Add light.
	LightPtr lamp = new Light(Light::Type::POINT);
	lamp->setPower(20.0);
	lamp->setPosition({4.3, 4.3, 4.3});
	scene->addLight(lamp);

	// Show scene.
	Engine engine;
	engine.setActiveScene(scene);
	engine.setDisplayFPS(true);
	engine.validateScene();
	engine.showScene();

	return 0;
}
