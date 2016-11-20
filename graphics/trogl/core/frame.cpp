#include "frame.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Frame::Frame(const std::string& title,
			 const size_t& posX,
			 const size_t& posY,
			 const size_t& width,
			 const size_t& height)
	: _width(width),
	  _height(height),
	  _glWindow(0)
{
	int argc = 1;
	char* argv[1] = {"engine"};

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(_width, _height);

	_glWindow = glutCreateWindow(title.c_str());
}


Frame::~Frame()
{
}


const size_t& Frame::getWidth() const
{
	return _width;
}


const size_t& Frame::getHeight() const
{
	return _height;
}


bool Frame::validate() const
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		logFatal << "Error in glewInit, code: " << err
				 << ", message: " << glewGetErrorString(err) << logEndl;
		return false;
	}
	else if (_glWindow == 0)
	{
		logFatal << "Invalid GL window: glutCreateWindow returned 0." << logEndl;
		return false;
	}

	return true;
}


void Frame::resize(const size_t& width,
				   const size_t& height)
{
	_width = width;
	_height = height;

	glViewport(0, 0, (GLsizei)_width, (GLsizei)_height);
}


void Frame::clear(const Color& color)
{
	glClearColor(color.getRedF(),
				 color.getGreenF(),
				 color.getBlueF(),
				 color.getAlphaF());

	glDepthFunc(GL_LESS);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Frame::flush()
{
	glFlush();
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
