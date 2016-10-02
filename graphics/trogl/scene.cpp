#include "scene.hpp"

#include <algorithm>
#include <logger.hpp>


const Camera Scene::DEFAULT_CAMERA = Camera();
const std::string Scene::DEFAULT_NAME = "Scene";


Scene::Scene(const std::string& name, const Camera& camera)
	: Component(Component::Type::SCENE, name),
	  _objects(),
	  _meshes(),
	  _lamps(),
	  _camera(camera),
	  _bgColor()
{
	_objects.push_back(&_camera);
	logDebug << "Scene with camera "
			 << _camera.getName() << " created" << logEnd;
}


Scene::~Scene()
{
	logDebug << "Scene removed" << logEnd;
}


void Scene::addMesh(const Mesh& mesh)
{
	_meshes.push_back(mesh);
	_objects.push_back(&_meshes.back());
	logDebug << "Mesh: " << _meshes.back().getName()
			 << " added to scene " << _name << logEnd;
}


void Scene::addLamp(const Lamp& lamp)
{
	_lamps.push_back(lamp);
	_objects.push_back(&_lamps.back());
	logDebug << "Lamp: " << _lamps.back().getName()
			 << " added to scene " << _name << logEnd;
}


const Objects& Scene::getObjects() const
{
	return _objects;
}


const Meshes& Scene::getMeshes() const
{
	return _meshes;
}


const Lamps& Scene::getLamps() const
{
	return _lamps;
}


const Camera& Scene::getCamera() const
{
	return _camera;
}


void Scene::setCamera(const Camera& camera)
{
	const Objects::iterator it = std::find(_objects.begin(), _objects.end(), &_camera);
	_objects.erase(it);
	logDebug << "Scene camera " << _camera.getName() << " (old)";
	_camera = camera;
	_objects.push_back(&_camera);
	logDebug << " replaced with " << _camera.getName() << " (new)" << logEnd;
}
