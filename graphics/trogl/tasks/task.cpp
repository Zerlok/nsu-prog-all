#include "task.hpp"


#include <logger.hpp>
#include "meshes/sphere.hpp"


logger_t moduleLogger = loggerModule(loggerLInfo, loggerDFull);


Task::Task(const std::string& name)
	: meshes({}),
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
		scene->addMesh(new Sphere());

	if (scene->getLights().empty())
		scene->addLight(new Light(Light::createSun()));

	return scene;
}
