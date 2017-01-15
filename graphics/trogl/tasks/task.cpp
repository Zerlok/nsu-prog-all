#include "task.hpp"


#include <logger.hpp>
#include "meshes/sphere.hpp"


logger_t moduleLogger = loggerModule(loggerLInfo, loggerDFull);


Task::Task(const std::string& name)
	: engine(Engine::instance()),
	  meshes({}),
	  lights({}),
	  camera(new Camera(1000, 800)),
	  scene(new Scene(name, camera))
{
	scene->setBgColor(Color::grey);
	scene->setAmbient(0.7);
	logInfo << scene->getName() << " created." << logEndl;
}


Task::~Task()
{
	logInfo << scene->getName() << " finished." << logEndl;
}


ScenePtr& Task::getScene()
{
	if (scene->getMeshes().empty())
	{
		scene->addMesh(new Sphere());
		logInfo << "Sphere added to empty scene." << logEndl;
	}

	if (scene->getLights().empty())
	{
		scene->addLight(new Light(Light::createSun()));
		logInfo << "Light added to empty scene." << logEndl;
	}

	return scene;
}


void Task::run()
{
	engine.enableFPS();
	engine.setActiveScene(getScene());
	engine.showActiveScene();
}


void Task::addDefaultCameraRotation()
{
	size_t T = 900;
	float h = 5.0;
	float a = 10.0;

	camera->setPosition({a, h, 0.0});
	camera->addKeyframe(T);
	camera->setPosition({0.0, h, -a});
	camera->addKeyframe(3*T/4);
	camera->setPosition({-a, h, 0.0});
	camera->addKeyframe(T/2);
	camera->setPosition({0.0, h, a});
	camera->addKeyframe(T/4);
	camera->setPosition({a, h, 0.0});
	camera->addKeyframe(0);

	AnimationPtr cameraRotation = new Animation("Camera rotation");
	cameraRotation->add(camera);
	cameraRotation->setLength(T);
	scene->addAnimation(cameraRotation);
	camera->setPosition({a, h, 0.0});
}


void Task::addDefaultSunRotation()
{
	size_t T = 400;
	float h = -1.0;
	float a = 1.0;

	LightPtr sun = new Light(Light::createSun());
	scene->addLight(sun);

	sun->setDirection({a, h, 0.0});
	sun->addKeyframe(T);
	sun->setDirection({0.0, h, -a});
	sun->addKeyframe(3*T/4);
	sun->setDirection({-a, h, 0.0});
	sun->addKeyframe(T/2);
	sun->setDirection({0.0, h, a});
	sun->addKeyframe(T/4);
	sun->setDirection({a, h, 0.0});
	sun->addKeyframe(0);

	AnimationPtr sunRotation = new Animation("Sun rotation");
	sunRotation->add(sun);
	sunRotation->setLength(T);
	scene->addAnimation(sunRotation);
}
