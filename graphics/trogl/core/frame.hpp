#ifndef __FRAME_HPP__
#define __FRAME_HPP__


#include <string>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "opengls.hpp"


class Frame
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
		class GLFrame
		{
			public:
				GLFrame(const std::string& title,
						const size_t& posX,
						const size_t& posY,
						const size_t& width,
						const size_t& height,
						const unsigned int& displayMode);
				GLFrame(const GLFrame&) = delete;
				~GLFrame();

				GLFrame& operator=(const GLFrame&) = delete;

				int getGLWindowNum() const;

			private:
				int _glWindow;
		};
};

using FramePtr = SharedPointer<Frame>;


class DoubleBufferedFrame : public Frame
{
	public:
		DoubleBufferedFrame(const std::string& title,
							const size_t& posX = 0,
							const size_t& posY = 0,
							const size_t& width = 512,
							const size_t& height = 512);
		~DoubleBufferedFrame();

		void flush() override;
};


#endif // __FRAME_HPP__
