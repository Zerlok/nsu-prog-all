#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "common/utils.hpp"
#include "common/color.hpp"

#include "meshes/cube.hpp"
#include "meshes/strangecube.hpp"
#include "meshes/megacube.hpp"
#include "meshes/cylinder.hpp"

#include "lamps/lamp.hpp"

#include "engine.hpp"
#include "engineutils.hpp"


loggerType lInstance = loggerInit(std::cout,
								  Logger::Level::INFO,
								  Logger::Description::FULL);


std::ostream& operator<<(std::ostream& out, const glm::vec3& v)
{
	out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return out;
}


int main(int argc, char *argv[])
{
	// Meshes generation settings.
	const size_t size = 3;
	const float offset = 2.5;
	const glm::vec3 cameraPos = glm::vec3(2*(size)*offset,
										  (size)*offset / 1.8,
										  (size)*offset);

	using MyMesh = MegaCube;
	const MyMesh clonableMesh = MegaCube(Color::white, Color::black);
//	using MyMesh = Cube;
//	const MyMesh clonableMesh = MyMesh(1.0, Color(220, 220, 220), 0);
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
	scene->addLight(new Lamp());

	// Show scene.
	Engine engine;
	engine.setActiveScene(scene);
	engine.setDisplayFPS(true);
	engine.validateScene();
	engine.showScene();

	return 0;
}
