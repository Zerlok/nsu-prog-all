#ifndef __BUFFER_FRAME_HPP__
#define __BUFFER_FRAME_HPP__


#include <string>
#include "frame.hpp"


class BufferFrame : public Frame
{
	public:
		// Constructors / Destructor.
		BufferFrame(const std::string& title,
					const size_t& posX = 0,
					const size_t& posY = 0,
					const size_t& width = 512,
					const size_t& height = 512);
		~BufferFrame();

		// Method.
		bool isBuffersValid() const;

		// Overriden methods.
		void init() override;
		bool validate() override;

		void clear(const Color& color) override;
		void flush() override;

	private:
		// Fields.
		GLuint _displayedBufer;
		GLuint _displayedTexture;
		GLuint _freshBuffer;
		GLuint _freshTexture;

		// Methods.
		void _initGLBufferAndTexture(GLuint& buffer, GLuint& texture);
};


#endif // __BUFFER_FRAME_HPP__
