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
	MeshPtr m = meshImporter.parse(input);
//	m->setRotation(0.0, 0.0, 1.07);
	scene->addMesh(m);

	camera->setPosition({0.0, 2.0, 6.0});
	engine.enableCameraRotation();
//	engine.setRenderMode(Engine::RenderMode::EDGES);
}
