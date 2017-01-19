#include "engine.hpp"


#include <sstream>
#include <cctype>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLDebug, (loggerDLevel | loggerDTime));


static const int WINDOW_POS_X = 2000;
static const int WINDOW_POS_Y = 100;
static const int ANIMATIONS_UPDATE_PERIOD = 50/3; // ms.
static const Engine::FrameType DEFAULT_FRAME_TYPE = Engine::FrameType::DOUBLE;


Engine& Engine::instance()
{
	static Engine e;
	return e;
}


Engine::Engine()
	: _status(),
	  _glRenderMode(RenderMode::POLYGONS),
	  _gui(nullptr),
	  _guiFPS(nullptr),
	  _scene(nullptr),
	  _camera(nullptr),
	  _primitives(),
	  _frameGenerator(nullptr),
	  _frame(nullptr),
	  _keyboard(Keyboard::instance()),
	  _mouse(Mouse::instance())
{
	setFrame(DEFAULT_FRAME_TYPE);
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

	// FIXME: unknown fails, when trying to run this code on HP-book.
	/* glslVersionsNum is strange.
	GLint glslVersionsNum;
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &glslVersionsNum);
	if (glslVersionsNum > 0)
	{
		log << "   versions (" << glslVersionsNum << "):";
		for (GLint i = 0; i < glslVersionsNum; ++i)
			log << std::endl << "      " << glGetStringi(GL_SHADING_LANGUAGE_VERSION, i);
	}
	*/

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

	if (!_scene->getAnimations().empty())
	{
		_animations = _scene->getAnimations();
		Logger& l = logInfo;
		l << "Scene " << _scene->getName() << " has " << _animations.size() << " animations:";
		for (const AnimationPtr& anim : _animations)
			l << std::endl << "   " << anim->getName();
		l << logEndl;
	}

	return 1;
}


int Engine::_validateFrame()
{
	_frame = _frameGenerator->create(
			_scene->getName(),
			WINDOW_POS_X,
			WINDOW_POS_Y,
			_camera->getWidth(),
			_camera->getHeight());

	_glVersion = _toString(GL_VERSION);
	_glShaderVersion = _toString(GL_SHADING_LANGUAGE_VERSION);

	if (!_frame->validate())
		return false;

	_frame->use();
	return true;
}


int Engine::_validatePrimitives()
{
	for (const MeshPtr& mesh : _scene->getMeshes())
	{
		Primitive obj(mesh);

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


int Engine::_validateLights()
{
	_lights = _scene->getLights();
	for (LightPtr& light : _lights)
	{
		ShaderPtr sh = light->getShader();
		if (sh.is_null())
			continue;

		sh->compile();
		if (!sh->isCompiledSuccessfully())
		{
			logError << "Invalid shader " << sh->getName() << " for light "
					 << light->getName() << logEndl;
			sh.release();
		}
	}

	return 1;
}


int Engine::_validateKeyboard()
{
	Keyboard::Code2KeyMap table;
	const int alphaLen = 'Z' - 'A' + 1;
	const int keyA = int(Keyboard::Key::A);
	for (int i = 0; i < alphaLen; ++i)
	{
		table['A' + i] = Keyboard::Key(keyA + i);
		table['a' + i] = Keyboard::Key(keyA + i);
	}

	table[GLUT_KEY_UP + 255] = Keyboard::Key::ARROW_UP;
	table[GLUT_KEY_DOWN + 255] = Keyboard::Key::ARROW_DOWN;
	table[GLUT_KEY_LEFT + 255] = Keyboard::Key::ARROW_LEFT;
	table[GLUT_KEY_RIGHT + 255] = Keyboard::Key::ARROW_RIGHT;

	_keyboard.setTranslationTable(table);
	return 1;
}


int Engine::_validateMouse()
{
	int x = _frame->getWidth() / 2;
	int y = _frame->getHeight() / 2;
	glutWarpPointer(x, y);
	_mouse.setPos(x, y);

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


void Engine::_glUpdateMatrices()
{
	_glMV = glm::lookAt(_camera->getPosition(),
						_camera->getLookingAtPosition(),
						_camera->getHeadDirection());
	_glMP = glm::perspective(_camera->getFOV(),
							 _camera->getWHRatio(),
							 _camera->getNearDistance(),
							 _camera->getFarDistance());
//	const float a = 5.0f;
//	_glMP = glm::ortho(-a, a, -a, a, _camera->getNearDistance(), _camera->getFarDistance());
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


void Engine::displayFPS(bool val)
{
	if (val && _guiFPS.is_null())
		_guiFPS = new GUIfps(10, 15, 20, 20);

	else if (!val)
		_guiFPS.release();
}


Keyboard& Engine::getKeyboard()
{
	return _keyboard;
}


Mouse&Engine::getMouse()
{
	return _mouse;
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
}


void Engine::setFrame(const FrameType& type)
{
	_status = Status::DIRTY;
	switch (type)
	{
		case FrameType::DOUBLE:
			_frameGenerator = new FrameGen<DoubleBufferFrame>();
			break;

		case FrameType::RTT:
			_frameGenerator = new FrameGen<RTTFrame>();
			break;

		default:
		case FrameType::SINGLE:
			_frameGenerator = new FrameGen<SingleBufferFrame>();
			break;
	}
}


void Engine::setRenderMode(const Engine::RenderMode& mode)
{
	_status = Status::DIRTY;
	_glRenderMode = mode;
}


void Engine::setFPSLimit(const size_t& val)
{
	_redisplayDelay = 1000 / val;
}


bool Engine::validate()
{
	int result = 0;
	result += _validateScene();
	result += _validateFrame();
	result += _validatePrimitives();
	result += _validateLights();
	result += _validateKeyboard();
	result += _validateMouse();

	_status = (result == 6)
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

	glutDisplayFunc(_displayFunc);
	glutReshapeFunc(_reshapeFunc);
	glutIdleFunc(_idleFunc);

	glutKeyboardFunc(_kbLetterDownFunc);
	glutKeyboardUpFunc(_kbLetterUpFunc);
	glutSpecialFunc(_kbSpecialDownFunc);
	glutSpecialUpFunc(_kbSpecialUpFunc);

	glutMouseFunc(_mouseClickFunc);
	glutMotionFunc(_mouseActiveMotionFunc);
	glutPassiveMotionFunc(_mousePassiveMotionFunc);

	if (_redisplayDelay > 0)
		glutTimerFunc(_redisplayDelay, _updateFrameFunc, 0);

	glutTimerFunc(ANIMATIONS_UPDATE_PERIOD, _updateAnimations, 0);

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

	_glUpdateMatrices();
	_frame->setViewMatrix(_glMV);
	_frame->setProjectionMatrix(_glMP);
	_frame->draw(_primitives, _lights, _camera);

	_viewGUI();

	_frame->flush();
}


void Engine::_displayFunc()
{
	instance()._viewFrame();
}


void Engine::_idleFunc()
{
	Engine& e = instance();

	e._keyboard.getHandler().handleEvents();
	e._mouse.getHandler().handleEvents();

	if (e._redisplayDelay == 0)
		glutPostRedisplay();
}


void Engine::_reshapeFunc(int width, int height)
{
	instance()._frame->resize(width, height);
}


void Engine::_kbLetterDownFunc(unsigned char key, int, int)
{
	instance()._keyboard.setKeyPressed(int(key));
}


void Engine::_kbLetterUpFunc(unsigned char key, int, int)
{
	instance()._keyboard.setKeyReleased(int(key));
}


void Engine::_kbSpecialDownFunc(int key, int, int)
{
	key += 255;
	instance()._keyboard.setKeyPressed(key);
}


void Engine::_kbSpecialUpFunc(int key, int, int)
{
	key += 255;
	instance()._keyboard.setKeyReleased(key);
}


void Engine::_mouseClickFunc(int button, int state, int x, int y)
{
	instance()._mouse.reset(button, state, x, y);
}


void Engine::_mouseActiveMotionFunc(int x, int y)
{
	instance()._mouse.moveTo(x, y);
}


void Engine::_mousePassiveMotionFunc(int x, int y)
{
	instance()._mouse.moveTo(x, y);
}


void Engine::_updateFrameFunc(int)
{
	glutTimerFunc(instance()._redisplayDelay, _updateFrameFunc, 0);
	glutPostRedisplay();
}


void Engine::_updateAnimations(int)
{
	for (AnimationPtr& anim : instance()._animations)
		anim->nextFrame();

	glutTimerFunc(ANIMATIONS_UPDATE_PERIOD, _updateAnimations, 0);
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
