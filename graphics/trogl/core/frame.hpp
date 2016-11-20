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
			  const size_t& width = 256,
			  const size_t& height = 256);
		virtual ~Frame();

		// Methods.
		const size_t& getWidth() const;
		const size_t& getHeight() const;

		// Virtual methods.
		virtual bool validate() const;
		virtual void resize(const size_t& width,
							const size_t& height);

		virtual void clear(const Color& color);
		virtual void flush();

	protected:
		// Fields.
		size_t _width;
		size_t _height;
		int _glWindow;
};

using FramePtr = SharedPointer<Frame>;


#endif // __FRAME_HPP__
