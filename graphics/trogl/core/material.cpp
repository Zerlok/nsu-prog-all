#include "material.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Material::Material(const std::string& name,
				   const Color& color,
				   const ShaderPtr& shader)
	: Component(Component::Type::MATERIAL, name),
	  _color(color),
	  _texturesLen(0.0),
	  _textures(),
	  _texturesMixing(0.5),
	  _shader(shader)
{
	logDebug << "Material: " << getName() << " with "
			  << ((!_shader.is_null()) ? _shader->getName() : "null shader") << " created."
			  << logEndl;
}


Material::Material(const Material& mat)
	: Component(mat),
	  _color(mat._color),
	  _texturesLen(mat._texturesLen),
	  _textures(mat._textures),
	  _texturesMixing(mat._texturesMixing),
	  _shader(mat._shader)
{
	logDebug << getName() << " material copied from " << mat.getName() << logEndl;
}


Material::Material(Material&& mat)
	: Component(mat),
	  _color(std::move(mat._color)),
	  _texturesLen(std::move(mat._texturesLen)),
	  _textures(std::move(mat._textures)),
	  _texturesMixing(std::move(mat._texturesMixing)),
	  _shader(std::move(mat._shader))
{
	logDebug << getName() << " material moved." << logEndl;
}


Material::~Material()
{
	logDebug << getName() << " material removed." << logEndl;
}


Material& Material::operator=(const Material& mat)
{
	Component::operator=(mat);
	_color = mat._color;
	_texturesMixing = mat._texturesMixing;
	_texturesLen = mat._texturesLen;
	_textures = mat._textures;
	_shader = mat._shader;

	logDebug << getName() << " material copied from " << mat.getName() << logEndl;
	return (*this);
}


Material& Material::operator=(Material&& mat)
{
	Component::operator=(mat);
	_color = std::move(mat._color);
	_texturesMixing = std::move(mat._texturesMixing);
	_texturesLen = std::move(mat._texturesLen);
	_textures = std::move(mat._textures);
	_shader = std::move(mat._shader);

	logDebug << getName() << " material moved." << logEndl;
	return (*this);
}


bool Material::isValid() const
{
	return _shader->isCompiledSuccessfully();
}


const Color& Material::getColor() const
{
	return _color;
}


const float& Material::getTextureMixing() const
{
	return _texturesMixing;
}


const Textures& Material::getTextures() const
{
	return _textures;
}


const ShaderPtr&Material::getShader() const
{
	return _shader;
}


void Material::compile()
{
	_shader->compile();

	_texturesMixing = (!_textures.empty()) ? _texturesMixing : 0.0;
	_texturesLen = _textures.size();
	for (TexturePtr& texture : _textures)
		texture->generate();

	logDebug << "Material " << getName() << " compiled ("
			 << "shader: " << _shader->getName() << ", textures: " << _textures.size() << ')'
			 << logEndl;
}


void Material::setColor(const Color& color)
{
	_color = color;
}


void Material::setTextureMixing(const float& mixing)
{
	_texturesMixing = mixing;
}


void Material::addTexture(const TexturePtr& texture)
{
	_textures.push_back(texture);
}


void Material::use()
{
	_shader->bind();

	for (TexturePtr& texture : _textures)
	{
		texture->bind();
		_shader->passComponent(texture);
	}

	_shader->passAttribute("material.color", _color);
	_shader->passAttribute("texturesMixing", _texturesMixing);
	_shader->passAttribute("texturesLen", _texturesLen);
}


void Material::_setShader(const ShaderPtr& shader)
{
	_shader = shader;
}
