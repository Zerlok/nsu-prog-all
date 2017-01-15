#include "scene.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


const CameraPtr Scene::DEFAULT_CAMERA = new Camera();


Scene::Scene(const std::string& name,
			 const CameraPtr& camera)
	: Component("SCENE", name),
	  _camera(camera),
	  _meshes(),
	  _lights(),
	  _animations(),
	  _bgColor(Color::grey),
	  _ambientPower(0.0)
{
	logDebug << "Scene " << getName()
			 << " with camera " << _camera->getName() << " created."
			 << logEndl;
}


Scene::Scene(const Scene& scene)
	: Component(scene),
	  _camera(scene._camera),
	  _meshes(scene._meshes),
	  _lights(scene._lights),
	  _animations(scene._animations),
	  _bgColor(scene._bgColor),
	  _ambientPower(scene._ambientPower)
{
	logDebug << "Scene " << getName()
			 << " copied from " << scene.getName()
			 << logEndl;
}


Scene::~Scene()
{
	logDebug << "Scene " << getName() << " removed." << logEndl;
}


Scene& Scene::operator=(const Scene& scene)
{
	_camera = scene._camera;
	_meshes = scene._meshes;
	_lights = scene._lights;
	_animations = scene._animations;
	_bgColor = scene._bgColor;
	_ambientPower = scene._ambientPower;

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


LightPtr Scene::getAmbientLight() const
{
	LightPtr light = new Light(Light::Type::AMBIENT);
	light->setColor(_bgColor);
	light->setPower(_ambientPower);

	return std::move(light);
}


const Animations&Scene::getAnimations() const
{
	return _animations;
}


void Scene::addMesh(const MeshPtr& mesh)
{
	_meshes.push_back(mesh);
	logDebug << "Mesh: " << _meshes.back()->getName()
			 << " added to scene " << getName() << logEndl;
}


void Scene::addLight(const LightPtr& light)
{
	_lights.push_back(light);
	logDebug << "Lamp: " << _lights.back()->getName()
			 << " added to scene " << getName() << logEndl;
}


void Scene::addAnimation(const AnimationPtr& animation)
{
	_animations.push_back(animation);
}


void Scene::setCamera(const CameraPtr& camera)
{
	logDebug << "Scene old camera " << _camera->getName();
	_camera = camera;
	logDebug << " replaced with new " << _camera->getName() << logEndl;
}



void Scene::setBgColor(const Color& color)
{
	_bgColor = color;
}


void Scene::setAmbient(const float& power)
{
	_ambientPower = power;
}
