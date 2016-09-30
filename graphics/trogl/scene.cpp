#include "scene.hpp"

#include <logger.hpp>


Scene::Scene()
	: _objects(),
	  _lamps(),
	  _meshes(),
	  _bgColor(),
	  _name()
{
	logDebug << "Scene created" << logEnd;
}


Scene::~Scene()
{
	logDebug << "Scene removed" << logEnd;
}


void Scene::addLamp(const Lamp& lamp)
{
	_lamps.push_back(lamp);
	_objects.push_back(&_lamps.back());
}


void Scene::addMesh(const Mesh& mesh)
{
	_meshes.push_back(mesh);
	_objects.push_back(&_meshes.back());
}
