#ifndef __TASK_HPP__
#define __TASK_HPP__


#include <string>
#include <sharedpointer.h>
#include "core/mesh.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"

#include "engine.hpp"


class Task
{
	public:
		Task(const std::string& name = "Unnamed task");
		virtual ~Task();

		ScenePtr& getScene();
		void run();

	protected:
		Engine& engine;
		Meshes meshes;
		Lights lights;
		CameraPtr camera;
		ScenePtr scene;

		void addDefaultCameraRotation();
		void addDefaultSunRotation();
};


using TaskPtr = SharedPointer<Task>;


#endif // __TASK_HPP__
