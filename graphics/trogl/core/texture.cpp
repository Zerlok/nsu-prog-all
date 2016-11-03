#include "texture.hpp"


#include <logger.hpp>


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name)
{
}


Texture::~Texture()
{
}
