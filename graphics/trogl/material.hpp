#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include "component.hpp"


class Material : public Component
{
	public:
		Material(const std::string& name = std::string());
		~Material();
};


#endif // __MATERIAL_HPP__
