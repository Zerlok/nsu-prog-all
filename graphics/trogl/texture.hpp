#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include "component.hpp"


class Texture : public Component
{
	public:
		Texture(const std::string& name = std::string());
		~Texture();
};


#endif // __TEXTURE_HPP__
