#include "magnetics.hpp"


#include "meshes/cylinder.hpp"


Magnet::Magnet()
	: _core(new Cylinder())
{
	_core->setScale({1.0, 2.0, 1.0});
}


Magnet::~Magnet()
{
}


const MeshPtr&Magnet::getCoreMesh() const
{

}


MeshPtr Magnet::calculateMagneticLines()
{
	/*
	 * H = 3(m, r)r / |r|^5 - m / |r|^3
	 */
}


MagneticVisualization::MagneticVisualization()
	: Task("Magnet Fields Visualization")
{
	Magnet m;

	scene->addMesh(m.getCoreMesh());
	scene->addMesh(m.calculateMagneticLines());

	camera->setPosition({0.0, 6.0, 20.0});
	engine.setRenderMode(Engine::RenderMode::EDGES);
}
