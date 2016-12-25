#include "engine.hpp"


#include <sstream>
#include <cctype>
#include <logger.hpp>
#include "common/utils.hpp"


#define TROGL_FRAME_TYPE DoubleBufferFrame
//#define TROGL_FRAME_TYPE RTRFrame


logger_t moduleLogger = loggerModule(loggerLDebug, (loggerDLevel | loggerDTime));


static const int WINDOW_POS_X = 2000;
static const int WINDOW_POS_Y = 100;


Engine& Engine::instance()
{
	static Engine e;
	return e;
}


Engine::Engine()
	: _status(),
	  _glRenderMode(RenderMode::POLYGONS),
	  _gui(nullptr),
	  _guiFPS(),
	  _scene(nullptr),
	  _camera(nullptr),
	  _primitives(),
	  _frame(nullptr)
{
	logDebug << "Engine created." << logEndl;
}


Engine::~Engine()
{
	logDebug << "Engine removed." << logEndl;
}


void Engine::_logEngineOptions() const
{
	Logger& log = logInfo;

	log << "TroGL engine uses OpenGL:"
		<< std::endl << "   OpenGL version: " << glGetString(GL_VERSION) << " (" << _glVersion << ')'
		<< std::endl << "   Vendor version: " << glGetString(GL_VENDOR)
		<< std::endl << "   Renderer version: " << glGetString(GL_RENDERER)
		<< std::endl << "   GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << " (" << _glShaderVersion << ')'
		<< std::endl;

	GLint glslLocationsCount;
	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &glslLocationsCount);

	log << "GLSL settings:"
		<< std::endl << "   GLSL max locations amount: " << glslLocationsCount
		<< std::endl;

	GLint glslVersionsNum;
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &glslVersionsNum);
	if (glslVersionsNum > 0)
	{
		log << "   versions (" << glslVersionsNum << "):";
		for (GLint i = 0; i < glslVersionsNum; ++i)
			log << std::endl << "      " << glGetStringi(GL_SHADING_LANGUAGE_VERSION, i);
	}

	log << logEndl;
}


void Engine::_logSceneStatistics() const
{
	size_t verticesNum = 0;
	size_t polygonsNum = 0;
	for (const MeshPtr& m : _scene->getMeshes())
	{
		verticesNum += m->getVertices().size();
		polygonsNum += m->getPolygons().size();
	}

	logInfo << "Scene: " << _scene->getName()
			<< " (" << _scene->getMeshes().size() << " meshes: "
			<< verticesNum << " vertices, "
			<< polygonsNum << " polygons, "
			<< _scene->getLights().size() << " lamps)"
			<< logEndl;
}


int Engine::_validateScene()
{
	if (_scene.is_null())
	{
		logError << "Cannot show scene - it was not set yet!" << logEndl;
		return 0;
	}

	_camera = _scene->getCamera();
	if (_camera.is_null())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << ", camera is null!"
				 << logEndl;
		return 0;
	}

	if (!_camera->isValid())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " with invalid camera " << _camera->getName()
				 << logEndl;
		return 0;
	}

	if (_scene->getMeshes().empty())
	{
		logError << "No meshes were found at scene " << _scene->getName()
				 << ", at least 1 mesh is required!"
				 << logEndl;
		return 0;
	}

	if (_scene->getLights().empty())
	{
		logError << "No lamps were found at scene " << _scene->getName()
				 << ", at least 1 lamp is required!"
				 << logEndl;
		return 0;
	}

	return 1;
}


int Engine::_validateFrame()
{
	bool result = _frame->validate();

	_glVersion = _toString(GL_VERSION);
	_glShaderVersion = _toString(GL_SHADING_LANGUAGE_VERSION);

	return (result) ? 1 : 0;
}


int Engine::_validatePrimitives()
{
	for (const MeshPtr& mesh : _scene->getMeshes())
	{
		Primitive obj {mesh};

		if (obj.isValid())
			_primitives.push_back(std::move(obj));
		else
			logWarning << "Invalid object " << mesh->getName()
					   << " will not be rendered." << logEndl;
	}

	if (_primitives.empty())
	{
		logError << "None valid mesh found in scene " << _scene->getName() << logEndl;
		return 0;
	}

	return 1;
}


void Engine::_glEnableOptions()
{
	glEnable(GL_TEXTURE_2D);
	logInfo << "GL Textures enabled." << logEndl;

	glEnable(GL_DEPTH_TEST);
	logInfo << "GL Depth enabled." << logEndl;

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	logInfo << "GL Face Culling enabled." << logEndl;

	glPolygonMode(GL_FRONT_AND_BACK, _glRenderMode);

	glShadeModel(GL_SMOOTH);
	logInfo << "GL Shading model SMOOTH set." << logEndl;
}


void Engine::_glInitProjectionMatrix()
{
	glm::mat4x4 mat = glm::perspective(_camera->getFOV(),
									   _camera->getWHRatio(),
									   _camera->getNearDistance(),
									   _camera->getFarDistance());
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&mat[0][0]);

	/* Old way
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_camera->getFOV(),
				   _camera->getWHRatio(),
				   _camera->getNearDistance(),
				   _camera->getFarDistance());
	*/
}


void Engine::_glInitModelViewMatrix()
{
	glm::mat4x4 mat = glm::lookAt(_camera->getPosition(),
								  _camera->getLookingAtPosition(),
								  _camera->getHeadDirection());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&mat[0][0]);
}


bool Engine::wasValidated() const
{
	switch (_status)
	{
		case Status::VALIDATION_FAILED:
		case Status::VALIDATION_SUCCESSFUL:
		case Status::RENDERING_STARTED:
		case Status::RENDERING_FINISHED:
			return true;

		case Status::DIRTY:
			return false;
	}

	return false;
}


bool Engine::isValid() const
{
	switch (_status)
	{
		case Status::VALIDATION_SUCCESSFUL:
		case Status::RENDERING_STARTED:
		case Status::RENDERING_FINISHED:
			return true;

		case Status::DIRTY:
		case Status::VALIDATION_FAILED:
			return false;
	}

	return false;
}


bool Engine::isRunning() const
{
	switch (_status)
	{
		case Status::RENDERING_STARTED:
			return true;

		case Status::DIRTY:
		case Status::VALIDATION_FAILED:
		case Status::VALIDATION_SUCCESSFUL:
		case Status::RENDERING_FINISHED:
			return false;
	}

	return false;
}


bool Engine::isStopped() const
{
	switch (_status)
	{
		case Status::RENDERING_FINISHED:
			return true;

		case Status::DIRTY:
		case Status::VALIDATION_FAILED:
		case Status::VALIDATION_SUCCESSFUL:
		case Status::RENDERING_STARTED:
			return false;
	}

	return false;
}


const Engine::Status& Engine::getStatus() const
{
	return _status;
}


void Engine::enableFPS()
{
	if (!_guiFPS.is_null())
		return;

	_guiFPS = new GUIfps(10, 15, 20, 20);
}


void Engine::disableFPS()
{
	_guiFPS.release();
}


void Engine::setGUI(const GUIPtr& gui)
{
	_status = Status::DIRTY;
	_gui = gui;
}


void Engine::setActiveScene(const ScenePtr& scene)
{
	_status = Status::DIRTY;
	_scene = scene;
	setActiveFrame(_scene->getFrameOfView<TROGL_FRAME_TYPE>());
}


void Engine::setActiveFrame(const FramePtr& frame)
{
	_status = Status::DIRTY;
	_frame = frame;
	_frame->setPos(WINDOW_POS_X, WINDOW_POS_Y);
}


void Engine::setRenderMode(const Engine::RenderMode& mode)
{
	_status = Status::DIRTY;
	_glRenderMode = mode;
}


bool Engine::validate()
{
	int result = 0;
	result += _validateScene();
	result += _validateFrame();
	result += _validatePrimitives();

	_status = (result == 3)
			? Status::VALIDATION_SUCCESSFUL
			: Status::VALIDATION_FAILED;

	return isValid();
}


void Engine::showActiveScene()
{
	if (!wasValidated()
			&& !validate())
		return;

	_status = Status::RENDERING_STARTED;
	logInfo << "Engine starts rendering..." << std::endl << logEndl;

	_logEngineOptions();
	_logSceneStatistics();

	_glEnableOptions();
	_glInitProjectionMatrix();
	_glInitModelViewMatrix();

	glutDisplayFunc(_displayFunc);
	glutReshapeFunc(_reshapeFunc);
	glutIdleFunc(_idleFunc);

	glutMainLoop();

	_status = Status::RENDERING_FINISHED;
	logInfo << "Engine rendering finished." << logEndl;
}


void Engine::_viewGUI()
{
	// TODO: use GUI shader.
	glUseProgram(0);

	// TODO: add comment description: what does each line do with GL.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // save
	glLoadIdentity();// and clear
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top

	const size_t& width = _frame->getWidth();
	const size_t& height = _frame->getHeight();

	if (!_guiFPS.is_null())
	{
		_guiFPS->tick();
		_guiFPS->draw(width, height);
	}

	if (!_gui.is_null())
	{
		for (const GUIComponentPtr& comp : _gui->getComponents())
			comp->draw(width, height);
	}

	glEnable(GL_DEPTH_TEST); // Turn depth testing back on

	// What does it do?
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // revert back to the matrix I had before.
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void Engine::_viewFrame()
{
	_frame->clear(_scene->getBgColor());

	// TODO: move into animation.
	// Camera flying.
	static const float a = std::sqrt(std::pow(_camera->getPosition().x, 2) + std::pow(_camera->getPosition().z, 2));
	static const float h = _camera->getPosition().y;
	const float psy = -getTimeDouble() / 29.0;
	const float phi = getTimeDouble() / 31.0;
//	_camera->setPosition({a*cos(phi), h, a*sin(phi)});
//	_glInitModelViewMatrix();

	LightPtr light = _scene->getLights().front();
	light->setPosition({a*cos(psy), light->getPosition().y, a*sin(psy)});
	light->faceDirectionTo({cos(-psy), 0.0, sin(-psy)});

	for (Primitive& obj : _primitives)
		for (const LightPtr& light : _scene->getLights())
			obj.draw(light, _camera);

	_viewGUI();
	_frame->flush();
}


void Engine::_reshape(int width, int height)
{
	_frame->resize(width, height);
}


void Engine::_displayFunc()
{
	instance()._viewFrame();
//	_debugGL();
}


void Engine::_idleFunc()
{
	glutPostRedisplay();
}


void Engine::_reshapeFunc(int width, int height)
{
	instance()._reshape(width, height);
}


void Engine::_debugGL()
{
	static GLenum err;
	err = glGetError();

	if (err != GL_NO_ERROR)
	{
		Logger& l = logError << "OpenGL errors:";
		do
		{
			l << std::endl << "   " << glewGetErrorString(err);
		}
		while ((err = glGetError()) != GL_NO_ERROR);
		l << logEndl;
	}
}


std::string Engine::_generateWindowTitle(const Scene& scene)
{
	std::stringstream ss;
	ss << "TroGL Engine [" << scene.getName() << ']';
	return ss.str();
}


std::string Engine::_toString(const GLenum& type)
{
	std::string str;

	const GLubyte* ptr = glGetString(type);
	while ((ptr != nullptr)
		   && ((*ptr) != '\0')
		   && ((*ptr) != ' '))
	{
		if (std::isalnum(*ptr))
			str.push_back(*ptr);

		++ptr;
	}

	for (size_t i = str.length(); i < 3; ++i)
		str.push_back('0');

	return std::move(str);
}
