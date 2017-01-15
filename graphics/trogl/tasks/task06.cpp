#include "task06.hpp"


#include <fstream>
#include "meshes/importexport.hpp"
#include "meshes/plane.hpp"


Task06ObjFileImportExport::Task06ObjFileImportExport()
	: Task("Task06 - .obj file Import")
{
	std::ifstream input("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");

	if (!input.is_open())
		std::cerr << "Cannot open file for " << scene->getName() << std::endl;

	Importer meshImporter;
	MeshPtr obj = meshImporter.parse(input);
	scene->addMesh(obj);

	MeshPtr floor = new Plane();
	floor->setPosition({0.0, -5.0, 0.0});
	floor->setScale({20.0, 1.0, 20.0});
	scene->addMesh(floor);

	addDefaultCameraRotation();
	addDefaultSunRotation();

//	engine.setRenderMode(Engine::RenderMode::EDGES);
}
