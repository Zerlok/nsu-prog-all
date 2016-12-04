#ifndef __FRAME_HPP__
#define __FRAME_HPP__


#include <string>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "opengls.hpp"
#include "component.hpp"


/*
 * Abstract frame. Implements a single buffer frame.
 */
class Frame : public Component
{
	public:
		// Constructors / Destructor.
		Frame(const std::string& title,
			  const size_t& posX = 0,
			  const size_t& posY = 0,
			  const size_t& width = 512,
			  const size_t& height = 512,
			  const unsigned int& displayMode = GLUT_RGBA);
		virtual ~Frame();

		// Methods.
		const size_t& getPosX() const;
		const size_t& getPosY() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;

		void setPos(const size_t& posX,
					const size_t& posY);

		// Virtual methods.
		virtual void init();

		virtual bool validate();
		virtual void resize(const size_t& width,
							const size_t& height);

		virtual void clear(const Color& color);
		virtual void flush();

	protected:
		// Fields.
		std::string _title;
		size_t _posX;
		size_t _posY;
		size_t _width;
		size_t _height;
		unsigned int _displayMode;
		int _glWindow;

	private:
		// Inner classes.
		class GLFrame
		{
			public:
				GLFrame(const std::string& title,
						const size_t& posX,
						const size_t& posY,
						const size_t& width,
						const size_t& height,
						const unsigned int& displayMode);
				~GLFrame();

				GLFrame(const GLFrame&) = delete;
				GLFrame& operator=(const GLFrame&) = delete;

				int getGLWindowNum() const;

			private:
				int _glWindow;
		};
};

using FramePtr = SharedPointer<Frame, Component>;
using SingleFrame = Frame;


/*
 * Double buffer frame (with displaying and drawing buffers).
 * A simple realisation using native OpenGL functions.
 */
class DoubleBufferFrame : public Frame
{
	public:
		// Constructors / Destructor.
		DoubleBufferFrame(const std::string& title,
						  const size_t& posX = 0,
						  const size_t& posY = 0,
						  const size_t& width = 512,
						  const size_t& height = 512);
		~DoubleBufferFrame();

		// Overriden methods.
		void flush() override;
};


/*
 * RenderToRenderbufferFrame. Renders into RenderBuffer, then displaying.
 */
class RTRFrame : public Frame
{
	public:
		// Constructors / Destructor.
		RTRFrame(const std::string& title,
				 const size_t& posX = 0,
				 const size_t& posY = 0,
				 const size_t& width = 512,
				 const size_t& height = 512);
		~RTRFrame();

		// Overriden methods.
		void init() override;
		void clear(const Color& color) override;
		void flush() override;

	private:
		// Fields.
		GLuint _fboId;
		GLuint _colorBuffer;
};


/*
 * Double buffer with attached textures.
 */
class TextureBufferFrame : public Frame
{
	public:
		// Constructors / Destructor.
		TextureBufferFrame(const std::string& title,
						   const size_t& posX = 0,
						   const size_t& posY = 0,
						   const size_t& width = 512,
						   const size_t& height = 512);
		~TextureBufferFrame();

		// Methods.
		bool isBuffersValid() const;

		// Overriden methods.
		void init() override;
		bool validate() override;

		void clear(const Color& color) override;
		void flush() override;

	private:
		// Fields.
		GLuint _frontBuffer;
		GLuint _frontTexture;
		GLuint _backBuffer;
		GLuint _backTexture;

		// Methods.
		void _initGLBufferAndTexture(GLuint& buffer, GLuint& texture);
		void _deinitGLBufferAndTexture(GLuint& buffer, GLuint& texture);
};



#endif // __FRAME_HPP__
