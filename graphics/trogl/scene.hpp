#ifndef __SCENE_HPP__
#define __SCENE_HPP__


#include <string>
#include <list>

#include "common/color.hpp"

#include "object.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "camera.hpp"


using Meshes = std::list<Mesh>;
using Lights = std::list<Light>;


class Scene : public Component
{
	public:
		Scene(const std::string& name = std::string(),
			  const Camera& camera = DEFAULT_CAMERA);
		Scene(const Scene& scene);
		~Scene();

		Scene& operator=(const Scene& scene);

		void addMesh(const Mesh& mesh);
		void addLight(const Light& lamp);

		const Meshes& getMeshes() const;
		const Lights& getLamps() const;

		const Camera& getCamera() const;
		void setCamera(const Camera& camera);

		const Color& getBgColor() const;
		void setBgColor(const Color& color);

	private:
		static const std::string DEFAULT_NAME;
		static const Camera DEFAULT_CAMERA;

		Meshes _meshes;
		Lights _lights;
		Camera _camera;

		Color _bgColor;
};


#endif // __SCENE_HPP__
