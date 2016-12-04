#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include <sharedpointer.h>
#include "component.hpp"


class Texture : public Component
{
	public:
		Texture(const std::string& name = "");
		~Texture();
};

using TexturePtr = SharedPointer<Texture, Component>;


#endif // __TEXTURE_HPP__
