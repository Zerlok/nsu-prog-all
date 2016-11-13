#ifndef __TROGL_ENGINE_UTILS_HPP__
#define __TROGL_ENGINE_UTILS_HPP__


#include <string>
#include <sharedpointer.h>
#include "core/object.hpp"

#include "core/mesh.hpp"
#include "meshes/cube.hpp"
#include "meshes/cylinder.hpp"
#include "meshes/megacube.hpp"


template<class T>
class ObjectGeneratorTraits
{
    public:
	using Pointer = SharedPointer<T>;
	using Array = std::vector<Pointer>;
};


template<class ObjectType, class GeneratorTraits=ObjectGeneratorTraits<ObjectType> >
class ObjectGenerator
{
    public:
	using ObjectPointer = typename GeneratorTraits::Pointer;
	using Objects = typename GeneratorTraits::Array;

	Objects latticeArrangement(
				const int& latticeSize,
				const float& latticeOffset,
				const ObjectType& parent) const
	{
	    glm::vec3 pos;
	    ObjectPointer obj;
	    Objects objVector(std::pow(2*latticeSize-1, 3));
	    size_t idx = 0;

	    for (int z = -latticeSize+1; z < latticeSize; ++z)
	    {
			for (int y = -latticeSize+1; y < latticeSize; ++y)
			{
				for (int x = -latticeSize+1; x < latticeSize; ++x)
				{
					pos.x = x*latticeOffset;
					pos.y = y*latticeOffset;
					pos.z = z*latticeOffset;

					obj = new ObjectType(parent);
					obj->setPosition(pos);
					objVector[idx++] = obj;
				}
			}
	    }

	    return std::move(objVector);
	}

	Objects directionArrangement(
			const size_t& size,
			const float& offset,
			const glm::vec3& direction,
			const ObjectType& parent
			) const
	{
		const glm::vec3 directionOffset = glm::normalize(direction) * offset;
		glm::vec3 pos {0.0, 0.0, 0.0};
		ObjectPointer obj;
		Objects objVector(size);

		for (size_t i = 0; i < size; ++i)
		{
			obj = new ObjectType(parent);
			obj->setPosition(pos);
			objVector[i] = obj;
			pos += directionOffset;
		}

		return std::move(objVector);
	}
};


#endif // __TROGL_ENGINE_UTILS_HPP__
