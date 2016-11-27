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
			  const size_t& height = 512);
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

		virtual bool validate() const;
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
		int _glWindow;

	private:
		class GLFrame
		{
			public:
				GLFrame(const std::string& title,
						const size_t& posX,
						const size_t& posY,
						const size_t& width,
						const size_t& height);
				GLFrame(const GLFrame&) = delete;
				~GLFrame();

				GLFrame& operator=(const GLFrame&) = delete;

				int getGLWindowNum() const;

			private:
				int _glWindow;
		};
};

using FramePtr = SharedPointer<Frame>;


#endif // __FRAME_HPP__
