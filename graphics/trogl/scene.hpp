#ifndef __SCENE_HPP__
#define __SCENE_HPP__


#include <string>
#include <list>

#include "common/color.hpp"

#include "object.hpp"
#include "lamp.hpp"
#include "mesh.hpp"


class Scene
{
	public:
		Scene();
		~Scene();

		void addLamp(const Lamp& lamp);
		void addMesh(const Mesh& mesh);

		const std::list<Object*> getObjects() const;
		const std::list<Lamp>& getLamps() const;
		const std::list<Mesh>& getMeshes() const;

		const std::string& getName() const;
		void setName(const std::string& name);

		const Color& getBgColor() const;
		void setBgColor(const Color& color);

	private:
		std::list<Object*> _objects;
		std::list<Lamp> _lamps;
		std::list<Mesh> _meshes;

		Color _bgColor;

		std::string _name;
};

#endif // __SCENE_HPP__
