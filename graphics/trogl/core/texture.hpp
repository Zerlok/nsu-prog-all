#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include <vector>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "animation.hpp"


class Texture : public Animatable
{
	public:
		enum class Filtering
		{
			NONE,
			BILINEAR,
			TRILINEAR,
			ANISOTROPIC,
		};

		enum class Wrapping
		{
			REPEATING,
			MIRRORED_REPEATING,
			EDGE_CLAMPING,
			BORDER_CLAMPING,
		};

		// Constructors / Destructor.
		Texture(const std::string& name);
		Texture(const Texture& text);
		Texture(Texture&& text);
		virtual ~Texture();

		// Operators.
		Texture& operator=(const Texture& text);
		Texture& operator=(Texture&& text);

		// Methods.
		const int& getSamplerId() const;

		const glm::vec2& getUVOffset() const;
		const glm::vec2& getUVScale() const;
		const float& getColorMix() const;
		const float& getNormal() const;

		void setUVOffset(const glm::vec2& offset);
		void setUVScale(const glm::vec2& scale);
		void setColorMix(const float& color);
		void setNormal(const float& normal);

		void setFiltering(const Filtering& type);
		void setWrapping(const Wrapping& type);

		void bind();
		void unbind();

		// Virtual methods.
		virtual void generate();

	protected:
		// Fields.
		int _id;
		GLuint _glTexture;

		glm::vec2 _uvOffset;
		glm::vec2 _uvScale;
		float _color;
		float _normal;

		Filtering _filtering;
		Wrapping _wrapping;
		bool _useMipmaps;

		void _create();
		void _regProperties() override;
};


using TexturePtr = SharedPointer<Texture, Animatable>;
using Textures = std::vector<TexturePtr>;


#endif // __TEXTURE_HPP__
