#include "texture.hpp"


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name)
{
}


Texture::~Texture()
{
}
