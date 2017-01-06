#include "task06.hpp"


#include <fstream>
#include "meshes/importexport.hpp"


Task06ObjFileImportExport::Task06ObjFileImportExport()
	: Task("Task06 - .obj file Import")
{
	std::ifstream input("/home/zerlok/nsu_prog/graphics/trogl/data/sphere.obj");

	if (!input.is_open())
		std::cerr << "Cannot open file for " << scene->getName() << std::endl;

	Importer meshImporter;

	Mesh m = meshImporter.parse(input);
	scene->addMesh(new Mesh(m));
}
