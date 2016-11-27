#include "bufferframe.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


BufferFrame::BufferFrame(const std::string& name,
						 const size_t& posX,
						 const size_t& posY,
						 const size_t& width,
						 const size_t& height)
	: Frame(name, posX, posY, width, height),
	  _displayedBufer(0),
	  _displayedTexture(0),
	  _freshBuffer(0),
	  _freshTexture(0)
{
}


BufferFrame::~BufferFrame()
{
}


bool BufferFrame::isBuffersValid() const
{
	// TODO: check buffers were allocated and prepare for viewing.
	return ((_displayedBufer != 0));
//			&& (_freshBuffer != 0));
}


void BufferFrame::init()
{
	Frame::init();

	_initGLBufferAndTexture(_displayedBufer, _displayedTexture);
//	_initGLBufferAndTexture(_freshBufer, _freshTexture);
}


bool BufferFrame::validate()
{
	if (!Frame::validate())
		return false;

	return isBuffersValid();
}


void BufferFrame::clear(const Color& color)
{
	// TODO: clear _fresh frame ONLY!
	Frame::clear(color);
}


void BufferFrame::flush()
{
	/*
	 * _fresh is a new frame, _displayed - the old frame.
	 * Displayed picture translates into buffer (_fresh),
	 * and fresh comes onto display (_displayed).
	 */
//	std::swap(_displayedBufer, _freshBuffer);
//	std::swap(_displayedTexture, _freshTexture);

	// TODO: show _displayed texture ONLY!
	glBindFramebuffer(GL_FRAMEBUFFER, _displayedBufer);
	glViewport(0, 0, _width, _height);
	Frame::flush();
}


void BufferFrame::_initGLBufferAndTexture(GLuint& buffer, GLuint& texture)
{
	glGenTextures(1, &texture);
	// "Bind" the newly created texture: all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	// Poor filtering is required!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_RGBA8, GL_TEXTURE_2D, texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


//void Frame::init(const size_t& width,
//							   const size_t& height)
//{
//	_width = width;
//	_height = height;

//	glGenFramebuffers(sizeof(_buffer), &_buffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, _buffer);

//	glGenTextures(sizeof(_frameTexture), &_frameTexture);
//	glBindTexture(GL_TEXTURE_2D, _frameTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//	// Set frame texture as our colour attachement #0
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _frameTexture, 0);
//	GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
//	glDrawBuffers(sizeof(drawBuffers), drawBuffers); // "1" is the size of DrawBuffers

//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		logError << "Frame buffer creation failed." << logEndl;
//}


//void Frame::bind()
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, _buffer);
//	glViewport(0, 0, _width, _height);
//}


//void Frame::unbind()
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}

