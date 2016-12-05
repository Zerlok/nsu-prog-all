#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__


#include <iostream>
#include <vector>
#include <memory>


class Image
{
	public:
		// Inner classes.
		enum class Format
		{
			JPG,
			PNG,
			BMP,
		};

		/*
		struct ByteRgb
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};

		struct ByteRgba
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		struct FloatRgb
		{
			float r;
			float g;
			float b;
		};

		struct FloatRgba
		{
			float r;
			float g;
			float b;
			float a;
		};

		union Pixel
		{
			ByteRgb px;
			ByteRgba px;
			FloatRgb px;
			FloatRgba px;
		};
		*/

		struct Pixel
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};

		// Constructors / Destructor.
		Image(const Format& format = Format::JPG);
		Image(std::istream& in, const Format& format = Format::JPG);
		Image(const Image& img);
		Image(Image&& img);
		~Image();

		// Operators.
		Image& operator=(const Image& img);
		Image& operator=(Image&& img);

		// Methods.
		bool isEmpty() const;

		const Format& getFormat() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		const size_t& getPixelsCount() const;
		const size_t& getPixelsSize() const;

		void setFormat(const Format& format);

		bool load(std::istream& in);
		bool save(std::ostream& out) const;

		Image copy() const;
		Image scale(const size_t& width, const size_t& height) const;

	private:
		// Static methods.
		static bool _loadJPGImage(std::istream& in, Image& img);
		static bool _loadPNGImage(std::istream& in, Image& img);
		static bool _loadBMPImage(std::istream& in, Image& img);

		// Fields.
		Format _format;
		size_t _width;
		size_t _height;
		std::shared_ptr<std::vector<Pixel>> _data;
};


#endif // __IMAGE_HPP__
