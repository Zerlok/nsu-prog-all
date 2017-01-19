#ifndef __FRAME_TEXTURE_HPP__
#define __FRAME_TEXTURE_HPP__


#include "core/texture.hpp"


class FrameTexture : public Texture
{
	public:
		enum class Type
		{
			COLOR,
			DEPTH,
		};

		FrameTexture(const Type& type,
					 const size_t& width,
					 const size_t& height);
		~FrameTexture();

		const GLuint& getBuffId() const;

		void generate() override;

	private:
		Type _type;
		size_t _width;
		size_t _height;
};


#endif // __FRAME_TEXTURE_HPP__
