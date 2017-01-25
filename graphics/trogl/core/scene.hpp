#ifndef __SCENE_HPP__
#define __SCENE_HPP__


#include <string>
#include <list>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "component.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "frame.hpp"


class Scene : public Component
{
	public:
		// Constructors / Destructor.
		Scene(const std::string& name,
			  const CameraPtr& camera);
		Scene(const Scene& scene);
		~Scene();

		// Operators.
		Scene& operator=(const Scene& scene);

		// Methods.
		const Meshes& getMeshes() const;
		const Lights& getLights() const;
		const Color& getBgColor() const;
		const CameraPtr& getCamera() const;
		LightPtr getAmbientLight() const;
		const Animations& getAnimations() const;

		void addMesh(const MeshPtr& mesh);
		void addLight(const LightPtr& light);
		void addAnimation(const AnimationPtr& animation);
		void setCamera(const CameraPtr& camera);
		void setBgColor(const Color& color);
		void setAmbient(const float& power);

	private:
		// Static fields.
		static const std::string DEFAULT_NAME;
		static const CameraPtr DEFAULT_CAMERA;

		// Fields.
		CameraPtr _camera;
		Meshes _meshes;
		Lights _lights;
		Animations _animations;

		Color _bgColor;
		float _ambientPower;
};

using ScenePtr = SharedPointer<Scene, Component>;


#endif // __SCENE_HPP__
