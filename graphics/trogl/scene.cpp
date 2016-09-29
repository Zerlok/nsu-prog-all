#include "scene.hpp"


Scene::Scene()
	: _objects(),
	  _lamps(),
	  _meshes(),
	  _bgColor(),
	  _name()
{
}


Scene::~Scene()
{
}


void Scene::addLamp(const Lamp& lamp)
{
	_lamps.push_back(lamp);
}


void Scene::addMesh(const Mesh& mesh)
{

}
