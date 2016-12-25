#ifndef __TASK_HPP__
#define __TASK_HPP__


#include <string>
#include <sharedpointer.h>
#include "core/mesh.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"


class Task
{
	public:
		Task(const std::string& name = "Unnamed task");
		virtual ~Task();

		ScenePtr& getScene();

	protected:
		Meshes meshes;
		Lights lights;
		CameraPtr camera;
		ScenePtr scene;
};


using TaskPtr = SharedPointer<Task>;


#endif // __TASK_HPP__
