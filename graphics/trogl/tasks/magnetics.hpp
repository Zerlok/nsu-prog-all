#ifndef __MAGNETICS_HPP__
#define __MAGNETICS_HPP__


#include "core/mesh.hpp"
#include "task.hpp"


class Magnet
{
	public:
		Magnet();
		virtual ~Magnet();

		const MeshPtr& getCoreMesh() const;
		MeshPtr calculateMagneticLines();

	protected:
		MeshPtr _core;
};


class MagneticVisualization : public Task
{
	public:
		MagneticVisualization();
		~MagneticVisualization() {}
};


#endif // __MAGNETICS_HPP__
