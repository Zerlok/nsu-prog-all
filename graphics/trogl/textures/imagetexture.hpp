#ifndef __IMAGE_TEXTURE_HPP__
#define __IMAGE_TEXTURE_HPP__


#include <QImage>
#include "core/texture.hpp"


class ImageTexture : public Texture
{
	public:
		ImageTexture(const std::string& filename);
		~ImageTexture();

		void generate() override;

	private:
		QImage _image;
};


#endif // __IMAGE_TEXTURE_HPP__
