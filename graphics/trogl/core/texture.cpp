#include "texture.hpp"


#include <logger.hpp>


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name)
{
}


Texture::~Texture()
{
}
