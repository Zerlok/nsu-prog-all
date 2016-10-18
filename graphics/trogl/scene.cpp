#include "scene.hpp"

#include <algorithm>
#include <logger.hpp>


const std::string Scene::DEFAULT_NAME = "Scene";
const CameraPtr Scene::DEFAULT_CAMERA = CameraPtr(new Camera());


Scene::Scene(const std::string& name,
			 const CameraPtr& camera)
	: Component(Component::Type::SCENE, name),
	  _camera(camera),
	  _meshes(),
	  _lights(),
	  _bgColor(Color::grey)
{
	logDebug << "Scene with camera "
			 << _camera->getName() << " created" << logEnd;
}


Scene::Scene(const Scene& scene)
	: Component(scene),
	  _camera(scene._camera),
	  _meshes(scene._meshes),
	  _lights(scene._lights),
	  _bgColor(scene._bgColor)
{
}


Scene::~Scene()
{
	logDebug << "Scene removed" << logEnd;
}


Scene& Scene::operator=(const Scene& scene)
{
	Component::operator=(scene);
	_camera = scene._camera;
	_meshes = scene._meshes;
	_lights = scene._lights;
	_bgColor = scene._bgColor;

	return (*this);
}


void Scene::addMesh(const MeshPtr& mesh)
{
	_meshes.push_back(mesh);
	logDebug << "Mesh: " << _meshes.back()->getName()
			 << " added to scene " << _name << logEnd;
}


void Scene::addLight(const LightPtr& lamp)
{
	_lights.push_back(lamp);
	logDebug << "Lamp: " << _lights.back()->getName()
			 << " added to scene " << _name << logEnd;
}


const Meshes& Scene::getMeshes() const
{
	return _meshes;
}


const Lights& Scene::getLamps() const
{
	return _lights;
}


const CameraPtr& Scene::getCamera() const
{
	return _camera;
}


void Scene::setCamera(const CameraPtr& camera)
{
	logDebug << "Scene old camera " << _camera->getName();
	_camera = camera;
	logDebug << " replaced with new " << _camera->getName() << logEnd;
}


const Color& Scene::getBgColor() const
{
	return _bgColor;
}


void Scene::setBgColor(const Color& color)
{
	_bgColor = color;
}
