#ifndef __FRAME_HPP__
#define __FRAME_HPP__


#include <string>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "opengls.hpp"
#include "component.hpp"
#include "textures/frametexture.hpp"
#include "primitive.hpp"
#include "light.hpp"
#include "camera.hpp"


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

		void setViewMatrix(const glm::mat4x4& mv);
		void setProjectionMatrix(const glm::mat4x4& mp);

		// Virtual methods.
		virtual void init();

		virtual bool validate();
		virtual void resize(const size_t& width,
							const size_t& height);

		virtual void use();
		virtual void clear(const Color& color);
		virtual void draw(const Primitives& primitives,
						  const Lights& lights,
						  const CameraPtr& camera);
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

		glm::mat4x4 _MV;
		glm::mat4x4 _MP;

		bool _checkFBO(GLuint& fbo) const;

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
using SingleBufferFrame = Frame;


class AbstractFrameGen
{
	public:
		AbstractFrameGen() {}
		virtual ~AbstractFrameGen() {}

		virtual FramePtr create(const std::string& title,
								const size_t& posX,
								const size_t& posY,
								const size_t& width,
								const size_t& height) = 0;
};

template<class F>
class FrameGen : public AbstractFrameGen
{
	public:
		FrameGen() {}
		~FrameGen() {}

		FramePtr create(const std::string &title,
						const size_t &posX,
						const size_t &posY,
						const size_t &width,
						const size_t &height) override
		{
			return new F(title, posX, posY, width, height);
		}
};

using FrameGenPtr = SharedPointer<AbstractFrameGen>;


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
 * Render To Texture Frame. Renders into Texture Image, then displaying it.
 */
class RTTFrame : public Frame
{
	public:
		// Constructors / Destructor.
		RTTFrame(const std::string& title,
				 const size_t& posX = 0,
				 const size_t& posY = 0,
				 const size_t& width = 512,
				 const size_t& height = 512);
		~RTTFrame();

		GLuint getFBO() const;
		GLuint getColorRBO() const;
		GLuint getDepthRBO() const;

		// Overriden methods.
		void init() override;
		bool validate() override;

		void use() override;
		void clear(const Color& color) override;
		void draw(const Primitives& primitives,
				  const Lights& lights,
				  const CameraPtr &camera) override;
		void flush() override;

	private:
		// Fields.
		GLuint _fboId;
		FrameTexture _colorTexture;
		FrameTexture _depthTexture;
		GLuint _depthRboId;
		Primitive* _screenPlane;
		ShaderPtr _ttsShader;
};


/*
 * Double buffer with attached textures.
 * http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
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
