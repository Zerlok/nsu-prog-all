#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


#include <vector>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "component.hpp"


class Texture : public Component
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
		virtual ~Texture();

		// Methods.
		const int& getSamplerId() const;

		const glm::vec2& getUVOffset() const;
		const glm::vec2& getUVScale() const;

		void setUVOffset(const glm::vec2& offset);
		void setUVScale(const glm::vec2& scale);

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
		float _normal;
		Filtering _filtering;
		Wrapping _wrapping;
		bool _useMipmaps;

		void _create();

	private:
		static int textureID;
};


using TexturePtr = SharedPointer<Texture, Component>;
using Textures = std::vector<TexturePtr>;


#endif // __TEXTURE_HPP__
