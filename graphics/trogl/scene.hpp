#ifndef __SCENE_HPP__
#define __SCENE_HPP__


#include <string>
#include <list>
#include <sharedpointer.h>

#include "common/color.hpp"

#include "object.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "camera.hpp"


using CameraPtr = SharedPointer<Camera>;
using MeshPtr = SharedPointer<Mesh>;
using LightPtr = SharedPointer<Light>;

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

		void addMesh(const MeshPtr& mesh);
		void addLight(const LightPtr& lamp);

		const Meshes& getMeshes() const;
		const Lights& getLamps() const;

		const CameraPtr& getCamera() const;
		void setCamera(const CameraPtr& camera);

		const Color& getBgColor() const;
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
