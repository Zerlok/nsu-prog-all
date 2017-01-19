#ifndef __FRAME_TEXTURE_HPP__
#define __FRAME_TEXTURE_HPP__


#include "core/texture.hpp"


class FrameTexture : public Texture
{
	public:
		FrameTexture(const size_t& width,
					 const size_t& height);
		~FrameTexture();

		const GLuint& getBuffId() const;

		void generate() override;

	private:
		size_t _width;
		size_t _height;
};


#endif // __FRAME_TEXTURE_HPP__
