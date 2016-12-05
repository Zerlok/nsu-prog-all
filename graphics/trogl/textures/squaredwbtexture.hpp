#ifndef __SQUARED_WB_TEXTURE_HPP__
#define __SQUARED_WB_TEXTURE_HPP__


#include <vector>
#include "core/texture.hpp"


class SquaredWBTexture : public Texture
{
	public:
		struct PixelRGB
		{
			PixelRGB(const float& r, const float& g, const float& b)
				: r(r), g(g), b(b) {}

			float r = 1.0f;
			float g = 1.0f;
			float b = 1.0f;
		};

		static const PixelRGB whitePixel;
		static const PixelRGB blackPixel;

		SquaredWBTexture(const size_t& width = 2,
						 const size_t& height = 2);
		~SquaredWBTexture();

		void generate() override;

	private:
		size_t _width;
		size_t _height;
		std::vector<PixelRGB> _pixels;
};


#endif // __SQUARED_WB_TEXTURE_HPP__
