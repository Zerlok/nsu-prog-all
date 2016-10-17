#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__


#include "object.hpp"


class Light : public Object
{
	public:
		enum class Type
		{
			POINT = 0,
			DIRCTIONAL = 1,
			SPOT = 2,
		};

		Light(const Type& type);
		Light(const Light& light);
		Light(Light&& light);
		~Light();

		Light& operator=(const Light& light);
		Light& operator=(Light&& light);

		const Type& getLightType() const;

	protected:
		Type _light_type;
};


#endif // __LIGHT_HPP__
