#include "scene.hpp"


#include <logger.hpp>


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


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
	logModule << "Scene with camera "
			 << _camera->getName() << " created" << logEndl;
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
	logModule << "Scene removed" << logEndl;
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


const Meshes& Scene::getMeshes() const
{
	return _meshes;
}


const Lights& Scene::getLights() const
{
	return _lights;
}


const Color& Scene::getBgColor() const
{
	return _bgColor;
}


const CameraPtr& Scene::getCamera() const
{
	return _camera;
}


CameraPtr& Scene::getCamera()
{
	return _camera;
}


void Scene::addMesh(const MeshPtr& mesh)
{
	_meshes.push_back(mesh);
	logModule << "Mesh: " << _meshes.back()->getName()
			 << " added to scene " << _name << logEndl;
}


void Scene::addLight(const LightPtr& light)
{
	_lights.push_back(light);
	logModule << "Lamp: " << _lights.back()->getName()
			 << " added to scene " << _name << logEndl;
}


void Scene::setCamera(const CameraPtr& camera)
{
	logModule << "Scene old camera " << _camera->getName();
	_camera = camera;
	logModule << " replaced with new " << _camera->getName() << logEndl;
}



void Scene::setBgColor(const Color& color)
{
	_bgColor = color;
}
