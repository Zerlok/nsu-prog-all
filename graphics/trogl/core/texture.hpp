#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include <vector>
#include <QImage>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "component.hpp"


class Texture : public Component
{
	public:
		// Constructors / Destructor.
		Texture(const std::string& filename);
		virtual ~Texture();

		// Methods.
		const glm::vec2& getUVOffset() const;
		const float& getColorMix() const;
		const float& getNormal() const;

		void generate();
		void bind();
		void unbind();

	protected:
		// Fields.
		GLuint _glTexture;

		glm::vec2 _uvOffset;
		float _colorMix;
		float _normal;

		QImage _image;
};

using TexturePtr = SharedPointer<Texture, Component>;
using Textures = std::vector<TexturePtr>;


#endif // __TEXTURE_HPP__
