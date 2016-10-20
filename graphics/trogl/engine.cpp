#include "engine.hpp"

#include <logger.hpp>
#include <sstream>
#include "common/utils.h"


// TODO: place default shaders into Material (default material shaders).
Engine* Engine::_current = nullptr;


Engine::Engine(bool displayFPS)
	: _scene(nullptr),
	  _gui(nullptr),
	  _guiFPS(),
	  _isValid(false),
	  _width(0),
	  _height(0)
{
	logDebug << "Engine init started" << logEnd;

	setDisplayFPS(displayFPS);

	// TODO: move glut init into "initialize" function, create bool _isInited for checks.
	int argc = 1;
	char* argv = "engine";
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(2000, 100);

	logDebug << "Engine created" << logEnd;
}


Engine::~Engine()
{
	logDebug << "Engine removed" << logEnd;
}


void Engine::setDisplayFPS(bool displayFPS)
{
	if (displayFPS)
		_guiFPS = new GUIfps(0, 0, 1, 1);
	else
		_guiFPS = nullptr;
}


void Engine::setGUI(const GUIPtr& gui)
{
	_gui = gui;
}


void Engine::setActiveScene(const ScenePtr& scene)
{
	_scene = scene;
}


void Engine::showScene()
{
	if (!_scene)
	{
		logError << "Cannot show scene - it was not set yet!" << logEnd;
		return;
	}

	const Camera& cam = _scene->getCamera().get_reference();
	glutInitWindowSize(
				cam.getWidth(),
				cam.getHeight());
	int sceneWindow = glutCreateWindow(_generateWindowName(*_scene).c_str());

	if (!_runGlewTest())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " - engine couldn't initialize" << logEnd;
		return;
	}

	if (!cam.isValid())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " - camera settings are invalid" << logEnd;
		return;
	}

	// TODO: make Engine as singleton.
	_current = this;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(cycle);

	// TODO: add light to scene.

	// TODO: add objects' materials (save shaders).
	for (const MeshPtr& m : _scene->getMeshes())
	{
		_objects.push_back(SingleVertexObject(m));
		SingleVertexObject& obj = _objects.back();
		obj.compileShaders();

		if (!obj.validate())
		{
			_objects.pop_back();
			logWarning << "Invalid object: " << m->getName()
					   << " not assigned." << logEnd;
		}
	}

	logInfo << "Engine rendering started (scene: " << _scene->getName() << ")" << logEnd;
	glutMainLoop();
	logInfo << "Engine rendering finished." << logEnd;

	glutDestroyWindow(sceneWindow);
}


void Engine::assignMeshToEngineObject(const MeshPtr& mesh)
{
	_objects.push_back(SingleVertexObject(mesh));
}


void Engine::drawGUI()
{
	// What does it do?
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // save
	glLoadIdentity();// and clear
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top

	if (_guiFPS)
	{
		_guiFPS->tick();
		drawGUILabel(*_guiFPS);
	}

	if (_gui)
	{
		for (const GUIComponentPtr& comp : _gui->getComponents())
		{
			switch (comp->getGuiComponentType())
			{
				case GUIComponent::Type::LABEL:
					drawGUILabel((const GUILabel&)(*comp));
					break;
				case GUIComponent::Type::PLANE:
					drawGUIPlane((const GUIPlane&)(*comp));
					break;
			}
		}
	}

	glEnable(GL_DEPTH_TEST); // Turn depth testing back on

	// What does it do?
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // revert back to the matrix I had before.
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void Engine::drawGUILabel(const GUILabel& glabel)
{
	// TODO: count position from gui component.
	glRasterPos2f(-0.9, +0.9);
	glColor4f(glabel.getFgColor().getRedF(),
			  glabel.getFgColor().getGreenF(),
			  glabel.getFgColor().getBlueF(),
			  glabel.getFgColor().getAlphaF());
	const char* p = glabel.getText().c_str();
	do
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
	while (*(++p));
}


void Engine::drawGUIPlane(const GUIPlane& gplane)
{
}


void Engine::renderFrame()
{
	// TODO: add comment description: what does each line do with GL.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	const Color& bg = _scene->getBgColor();
	glClearColor(bg.getRedF(),
				 bg.getGreenF(),
				 bg.getBlueF(),
				 bg.getAlphaF());
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	// Matrix Projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const CameraPtr& cam = _scene->getCamera();
	_width = cam->getWidth();
	_height = cam->getHeight();
	gluPerspective(cam->getFOV(),
				   (GLdouble)_width/(GLdouble)_height,
				   cam->getLowDistance(),
				   cam->getHighDistance());

	// TODO: create camera lookAt method, which returns the position where does camera look at.
	const glm::mat4x4 matView  = glm::lookAt(cam->getPosition(),
											 cam->getLookingAtPosition(),
											 cam->getHeadDirection());

	// Drawing.
	// TODO: draw every object with its material (load its shaders).
	for (SingleVertexObject& obj : _objects)
	{
		obj.loadGeometry();
		obj.loadShaders();
		obj.draw(matView);
		obj.unloadShaders();
		obj.unloadGeometry();
	}

	// Draw GUI at the end of frame (to overlay over every objects on scene).
	drawGUI();

	// In the end.
	glFlush();
}


std::string Engine::_generateWindowName(const Scene& scene)
{
	std::stringstream ss;
	ss << "TroGL Engine [" << scene.getName() << "]";
	return ss.str();
}


bool Engine::_runGlewTest()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		logFatal << "Error in glewInit, code: " << err
				 << ", message: " << glewGetErrorString(err) << logEnd;
		return false;
	}

	return true;
}


void Engine::display()
{
	_current->renderFrame();
}


void Engine::reshape(int w, int h)
{
	float& width = _current->_width;
	float& height = _current->_height;

	width = w;
	height = h;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0);
}


void Engine::cycle()
{
	glutPostRedisplay();
}


// --------------------- SINGLE VERTEX OBJECT --------------------- //

const size_t Engine::SingleVertexObject::_vertexStep = 4;
const size_t Engine::SingleVertexObject::_colorStep = 4;
const size_t Engine::SingleVertexObject::_indexStep = 3;


Engine::SingleVertexObject::SingleVertexObject(const MeshPtr& mesh)
	: _glVBO(),
	  _glCBO(),
	  _glIBO(),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram(),
	  _glShadersCompileCount(0),
	  _vertices((mesh->getVertices().size() * _vertexStep), 0.0f),
	  _colors((mesh->getVertices().size() * _colorStep), 1.0f),
	  _indicies((mesh->getFaces().size() * _indexStep), 0.0f),
	  _vertexShader(mesh->getMaterial()->getVertexShader()),
	  _fragmentShader(mesh->getMaterial()->getFragmentShader()),
	  _mesh(mesh)
{
	/* Apply mesh vertices positions from object attributes
	 * (in reverse order: scale, rotation, position).
	 */
	_mesh->applyScale();
	_mesh->applyRotation();
	_mesh->applyPosition();

	size_t idx;
	// add vertecies and colors.
	idx = 0;
	for (size_t i = 0; i < _vertices.size(); i += _vertexStep)
	{
		const Mesh::Vertex& v = _mesh->getVertex(idx++);

		_vertices[i] = v.getPosition().x;
		_vertices[i+1] = v.getPosition().y;
		_vertices[i+2] = v.getPosition().z;
		_vertices[i+3] = 1.0f;

		_colors[i] = v.getColor().getRedF();
		_colors[i+1] = v.getColor().getGreenF();
		_colors[i+2] = v.getColor().getBlueF();
		_colors[i+3] = v.getColor().getAlphaF();
	}

	// add indicies from mesh faces.
	idx = 0;
	for (size_t i = 0; i < _indicies.size(); i += _indexStep)
	{
		const Mesh::Face& f = _mesh->getFace(idx++);

		_indicies[i] = f.getFirstIndex();
		_indicies[i+1] = f.getSecondIndex();
		_indicies[i+2] = f.getThirdIndex();
	}
}


Engine::SingleVertexObject::SingleVertexObject(Engine::SingleVertexObject&& obj)
	: _glVBO(std::move(obj._glVBO)),
	  _glCBO(std::move(obj._glCBO)),
	  _glIBO(std::move(obj._glIBO)),
	  _glVertexShader(std::move(obj._glVertexShader)),
	  _glFragmentShader(std::move(obj._glFragmentShader)),
	  _glShaderProgram(std::move(obj._glShaderProgram)),
	  _glShadersCompileCount(std::move(obj._glShadersCompileCount)),
	  _vertices(std::move(obj._vertices)),
	  _colors(std::move(obj._colors)),
	  _indicies(std::move(obj._indicies)),
	  _vertexShader(std::move(obj._vertexShader)),
	  _fragmentShader(std::move(obj._fragmentShader)),
	  _mesh(obj._mesh)
{
}


Engine::SingleVertexObject::~SingleVertexObject()
{
	glDeleteBuffers(sizeof(_glVBO), &_glVBO);
	glDeleteBuffers(sizeof(_glIBO), &_glIBO);
	glDeleteBuffers(sizeof(_glVBO), &_glCBO);
	logDebug << "Objects geometry removed" << logEnd;

	switch (_glShadersCompileCount)
	{
		case 3:
			glDetachShader(_glShaderProgram, _glVertexShader);
			glDetachShader(_glShaderProgram, _glFragmentShader);
			glDeleteProgram(_glShaderProgram);

		case 2:
			glDeleteShader(_glFragmentShader);

		case 1:
			glDeleteShader(_glVertexShader);

		case 0:
		default:
			break;
	}

	logDebug << "Shaders deinited." << logEnd;
}


void Engine::SingleVertexObject::loadGeometry()
{
	glGenBuffers(1, &_glVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), _vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_glIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicies.size() * sizeof(GLfloat), _indicies.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_glCBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glCBO);
	glBufferData(GL_ARRAY_BUFFER, _colors.size() * sizeof(GLuint), _colors.data(), GL_STATIC_DRAW);
}


void Engine::SingleVertexObject::loadShaders()
{
	glUseProgram(_glShaderProgram);
}


void Engine::SingleVertexObject::unloadGeometry()
{

}


void Engine::SingleVertexObject::unloadShaders()
{
	glUseProgram(0);
}


bool Engine::SingleVertexObject::validate() const
{
	if (_glShadersCompileCount != 3)
		return false;

	return true;
}


bool Engine::SingleVertexObject::compileShaders()
{
	_compileVertexShader();
	_compileFragmentShader();
	_compileShaderProgram();

	if (_glShadersCompileCount != 3)
		return false;

	_attrConstColor = glGetUniformLocation(_glShaderProgram, "constColor");
	_attrObjCenterPosition = glGetAttribLocation(_glShaderProgram, "objCenterPosition");

	_vertexShader->initUniformsLocations(_glShaderProgram);
	_fragmentShader->initUniformsLocations(_glShaderProgram);

	return true;
}


void Engine::SingleVertexObject::draw(const glm::mat4x4& mat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&mat[0][0]);

	const glm::vec3& pos = _mesh->getPosition();
	glUniform4f(_attrConstColor, 3, 3, 3, 1);
	glUniform3f(_attrObjCenterPosition, pos.x, pos.y, pos.z);
	_vertexShader->prepareForRender();
	_fragmentShader->prepareForRender();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glCBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glDrawElements(GL_TRIANGLES, _indicies.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


bool Engine::SingleVertexObject::_compileVertexShader()
{
	int success = 0;
	const char* vsSrc = _vertexShader->getSrcPtr();

	_glVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_glVertexShader, 1, &vsSrc, NULL);
	glCompileShader(_glVertexShader);
	glGetShaderiv(_glVertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_glVertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << _vertexShader->getName()
				 << "compilation:\n" << infoLog << logEnd;

		return false;
	}

	++_glShadersCompileCount;
	logDebug << _vertexShader->getName() << " compiled successfuly." << logEnd;
	return true;
}


bool Engine::SingleVertexObject::_compileFragmentShader()
{
	if (_glFragmentShader < 1)
		return false;

	int success = 0;
	const char* fsSrc = _fragmentShader->getSrcPtr();

	_glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_glFragmentShader, 1, &(fsSrc), NULL);
	glCompileShader(_glFragmentShader);
	glGetShaderiv(_glFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_glFragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << _fragmentShader->getName()
				 << " compilation:\n" << infoLog << logEnd;

		return false;
	}

	++_glShadersCompileCount;
	logDebug << _fragmentShader->getName() << " compiled successfuly." << logEnd;
	return true;
}


bool Engine::SingleVertexObject::_compileShaderProgram()
{
	if (_glShadersCompileCount < 2)
		return false;

	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	_glShaderProgram = glCreateProgram();
	glAttachShader(_glShaderProgram, _glVertexShader);
	glAttachShader(_glShaderProgram, _glFragmentShader);

	glBindAttribLocation(_glShaderProgram, 0, "position");
	glBindAttribLocation(_glShaderProgram, 1, "colors");

	glLinkProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in program linkage: " << infoLog << logEnd;
		return false;
	}

	logDebug << "Shader program linked successfuly." << logEnd;

	glValidateProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in program validation: " << infoLog << logEnd;
		return false;
	}

	++_glShadersCompileCount;
	logDebug << "Shader program is valid. Shaders compilation finished." << logEnd;
	return true;
}
