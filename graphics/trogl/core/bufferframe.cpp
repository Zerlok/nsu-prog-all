#include "bufferframe.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


BufferFrame::BufferFrame(const std::string& title,
						 const size_t& posX,
						 const size_t& posY,
						 const size_t& width,
						 const size_t& height)
	: Frame(title, posX, posY, width, height, GLUT_RGBA),
	  _displayedBufer(0),
	  _displayedTexture(0),
	  _freshBuffer(0),
	  _freshTexture(0)
{
	logDebug << "Buffer frame created." << logEndl;
}


BufferFrame::~BufferFrame()
{
	if (!isBuffersValid())
		return;

	glDeleteTextures(1, &_displayedTexture);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &_displayedBufer);

	logDebug << "Buffer frame removed." << logEndl;
}


bool BufferFrame::isBuffersValid() const
{
	return true;
	// TODO: check buffers were allocated and prepare for viewing.
//	return ((_displayedBufer != 0)
//			&& (_freshBuffer != 0));
}


void BufferFrame::init()
{
	logDebug << "Initialization started." << logEndl;

	Frame::init();

	_initGLBufferAndTexture(_displayedBufer, _displayedTexture);
//	_initGLBufferAndTexture(_freshBufer, _freshTexture);

	logDebug << "Initialization finished." << logEndl;
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
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _displayedBufer);
	Frame::clear(color);

	logDebug << "Buffer is clear." << logEndl;
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
	glViewport(0, 0, _width, _height);
	Frame::flush();

	logDebug << "Buffer was displayed." << logEndl;
}


void BufferFrame::_initGLBufferAndTexture(GLuint& buffer, GLuint& texture)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

	logDebug << "@ FBO: " << &buffer << logEndl;
	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	logDebug << "Texture: " << texture << ", FBO: " << buffer << logEndl;
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

