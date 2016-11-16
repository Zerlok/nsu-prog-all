#include "texture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name)
{
}


Texture::~Texture()
{
}
