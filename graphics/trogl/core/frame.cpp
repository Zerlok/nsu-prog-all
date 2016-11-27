#include "frame.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


Frame::Frame(const std::string& title,
			 const size_t& posX,
			 const size_t& posY,
			 const size_t& width,
			 const size_t& height,
			 const unsigned int& displayMode)
	: _title(title),
	  _posX(posX),
	  _posY(posY),
	  _width(width),
	  _height(height),
	  _displayMode(displayMode)
{
	logDebug << "Frame " << _title
			 << " [" << _width << "x" << _height << "] created."
			 << logEndl;
}


Frame::~Frame()
{
	logDebug << "Frame " << _title << " removed." << logEndl;
}


const size_t& Frame::getWidth() const
{
	return _width;
}


const size_t& Frame::getHeight() const
{
	return _height;
}


void Frame::setPos(const size_t& posX, const size_t& posY)
{
	_posX = posX;
	_posY = posY;
}


void Frame::init()
{
	static GLFrame glFrame(_title, _posX, _posY, _width, _height, _displayMode);
	_glWindow = glFrame.getGLWindowNum();
}


bool Frame::validate()
{
	init();

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


Frame::GLFrame::GLFrame(const std::string& title,
						const size_t& posX,
						const size_t& posY,
						const size_t& width,
						const size_t& height,
						const unsigned int& displayMode)
{
	logDebug << "Starting GL frame initialization started." << logEndl;

	int argc = 1;
	char* argv[1] = {"engine"};

	glutInit(&argc, argv);
	glutInitDisplayMode(displayMode);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(width, height);

	_glWindow = glutCreateWindow(title.c_str());

	logDebug << "GL frame initialization finished." << logEndl;
}


Frame::GLFrame::~GLFrame()
{
//	glutDestroyWindow(_glWindow);
	logDebug << "GL frame deinitialized." << logEndl;
}


int Frame::GLFrame::getGLWindowNum() const
{
	return _glWindow;
}


DoubleBufferedFrame::DoubleBufferedFrame(const std::string& title,
										 const size_t& posX,
										 const size_t& posY,
										 const size_t& width,
										 const size_t& height)
	: Frame(title, posX, posY, width, height, (GLUT_RGBA | GLUT_DOUBLE))
{
}


DoubleBufferedFrame::~DoubleBufferedFrame()
{
}


void DoubleBufferedFrame::flush()
{
	glutSwapBuffers();
}
