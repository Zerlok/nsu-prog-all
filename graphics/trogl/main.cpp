#include <iostream>
#include <logger.hpp>

#include "engine.hpp"
#include "meshcube.hpp"



int main(int argc, char *argv[])
{
	Logger::init(std::cout, Logger::Level::DEBUG);

	Scene scene;
	scene.addLamp(Lamp());
	scene.addMesh(Mesh());
	scene.addMesh(Mesh(Point(100, 2, 37.4)));

	scene.addMesh(MeshCube(1.0, 1.0, 1.0));

	TroglEngine engine;
	engine.showScene(scene);

	return 0;
}
