#ifndef __SCENE_HPP__
#define __SCENE_HPP__


#include <string>
#include <list>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "camera.hpp"


using Meshes = std::list<MeshPtr>;
using Lights = std::list<LightPtr>;


class Scene : public Component
{
	public:
		Scene(const std::string& name,
			  const CameraPtr& camera);
		Scene(const Scene& scene);
		~Scene();

		Scene& operator=(const Scene& scene);

		const Meshes& getMeshes() const;
		const Lights& getLamps() const;
		const Color& getBgColor() const;
		const CameraPtr& getCamera() const;

		void addMesh(const MeshPtr& mesh);
		void addLight(const LightPtr& lamp);
		void setCamera(const CameraPtr& camera);
		void setBgColor(const Color& color);

	private:
		static const std::string DEFAULT_NAME;
		static const CameraPtr DEFAULT_CAMERA;

		CameraPtr _camera;
		Meshes _meshes;
		Lights _lights;

		Color _bgColor;
};

using ScenePtr = SharedPointer<Scene>;


#endif // __SCENE_HPP__
