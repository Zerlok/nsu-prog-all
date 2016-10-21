#include "engine.hpp"


#include <sstream>
#include <logger.hpp>
#include "common/utils.h"


loggerType loggerInstance = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


Engine* Engine::_current = nullptr;


Engine::Engine(bool displayFPS)
	: _scene(nullptr),
	  _gui(nullptr),
	  _guiFPS(),
	  _isValid(false),
	  _width(0),
	  _height(0)
{
	logModule << "Engine init started" << logEndl;

	setDisplayFPS(displayFPS);

	// TODO: move glut init into "initialize" function, create bool _isInited for checks.
	int argc = 1;
	char* argv = "engine";
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(2000, 100);

	logModule << "Engine created" << logEndl;
}


Engine::~Engine()
{
	logModule << "Engine removed" << logEndl;
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
		logError << "Cannot show scene - it was not set yet!" << logEndl;
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
				 << " - engine couldn't initialize" << logEndl;
		return;
	}

	if (!cam.isValid())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " - camera settings are invalid" << logEndl;
		return;
	}

	// TODO: make Engine as singleton.
	_current = this;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(cycle);

	// TODO: add light to scene.

	for (const MeshPtr& m : _scene->getMeshes())
	{
		_objects.push_back(SingleVertexObject(m));
		SingleVertexObject& obj = _objects.back();
		obj.initGLGeometry();
		obj.compileGLShaders();

		if (!obj.isValid())
		{
			logWarning << "Invalid object: " << m->getName()
					   << " not assigned." << logEndl;
			_objects.pop_back();
		}
	}

	logInfo << "Engine rendering started (scene: " << _scene->getName() << ")" << logEndl;
	glutMainLoop();
	logInfo << "Engine rendering finished." << logEndl;

	glutDestroyWindow(sceneWindow);
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

	const glm::mat4x4 matView  = glm::lookAt(cam->getPosition(),
											 cam->getLookingAtPosition(),
											 cam->getHeadDirection());

	// Draw the objects.
	for (SingleVertexObject& obj : _objects)
		obj.draw(matView);

	// Draw GUI at the end of frame (to overlay over every objects on scene).
	drawGUI();

	// In the end.
	glFlush();
}


std::string Engine::_generateWindowName(const Scene& scene)
{
	std::stringstream ss;
	ss << "TroGL Engine [" << scene.getName() << ']';
	return ss.str();
}


bool Engine::_runGlewTest()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		logFatal << "Error in glewInit, code: " << err
				 << ", message: " << glewGetErrorString(err) << logEndl;
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
	: _glVBO(0),
	  _glCBO(0),
	  _glIBO(0),
	  _attrObjCenterPosition(0),
	  _indicesSize(0),
	  _shader(mesh->getMaterial()->getShader()),
	  _mesh(mesh)
{
	/* Apply mesh vertices positions from object attributes
	 * (in reverse order: scale, rotation, position).
	 */
	_mesh->applyScale();
	_mesh->applyRotation();
	_mesh->applyPosition();
}


Engine::SingleVertexObject::SingleVertexObject(Engine::SingleVertexObject&& obj)
	: _glVBO(std::move(obj._glVBO)),
	  _glCBO(std::move(obj._glCBO)),
	  _glIBO(std::move(obj._glIBO)),
	  _attrObjCenterPosition(std::move(obj._attrObjCenterPosition)),
	  _indicesSize(std::move(obj._indicesSize)),
	  _shader(std::move(obj._shader)),
	  _mesh(std::move(obj._mesh))
{
	obj._glVBO = 0;
	obj._glCBO = 0;
	obj._glIBO = 0;
}


Engine::SingleVertexObject::~SingleVertexObject()
{
	deinitGLGeometry();
	deinitGLShaders();
}


bool Engine::SingleVertexObject::isValid() const
{
	return ((_glVBO != 0)
			&& (_glCBO != 0)
			&& (_glIBO != 0)
			&& _shader->isValid());
}


void Engine::SingleVertexObject::initGLGeometry()
{
	_initVertexBufferObject();
	_initColorBufferObject();
	_initIndexBufferObject();
}


void Engine::SingleVertexObject::_initVertexBufferObject()
{
	std::vector<GLfloat> vertices((_mesh->getVertices().size() * _vertexStep), 0.0f);
	size_t idx = 0;

	for (size_t i = 0; i < vertices.size(); i += _vertexStep)
	{
		const Mesh::Vertex& v = _mesh->getVertex(idx++);

		vertices[i] = v.getPosition().x;
		vertices[i+1] = v.getPosition().y;
		vertices[i+2] = v.getPosition().z;
		vertices[i+3] = 1.0f;
	}

	glGenBuffers(1, &_glVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}


void Engine::SingleVertexObject::_initColorBufferObject()
{
	std::vector<GLfloat> colors((_mesh->getVertices().size() * _colorStep), 1.0f);
	size_t idx = 0;

	for (size_t i = 0; i < colors.size(); i += _colorStep)
	{
		const Mesh::Vertex& v = _mesh->getVertex(idx++);

		colors[i] = v.getColor().getRedF();
		colors[i+1] = v.getColor().getGreenF();
		colors[i+2] = v.getColor().getBlueF();
		colors[i+3] = v.getColor().getAlphaF();
	}

	glGenBuffers(1, &_glCBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glCBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLuint), colors.data(), GL_STATIC_DRAW);
}


void Engine::SingleVertexObject::_initIndexBufferObject()
{
	std::vector<GLuint> indicies((_mesh->getFaces().size() * _indexStep), 0.0f);
	size_t idx = 0;

	for (size_t i = 0; i < indicies.size(); i += _indexStep)
	{
		const Mesh::Face& f = _mesh->getFace(idx++);

		indicies[i] = f.getFirstIndex();
		indicies[i+1] = f.getSecondIndex();
		indicies[i+2] = f.getThirdIndex();
	}
	_indicesSize = indicies.size() * sizeof(GLuint);

	glGenBuffers(1, &_glIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, indicies.data(), GL_STATIC_DRAW);
}


void Engine::SingleVertexObject::compileGLShaders()
{
	_shader->compile();

	if (_shader->isValid())
		_attrObjCenterPosition = glGetUniformLocation(_shader->getProgram(), "objCenterPosition");
}


void Engine::SingleVertexObject::deinitGLGeometry()
{
	if (!isValid())
		return;

	glDeleteBuffers(sizeof(_glVBO), &_glVBO);
	glDeleteBuffers(sizeof(_glCBO), &_glCBO);
	glDeleteBuffers(sizeof(_glIBO), &_glIBO);

	logModule << "Objects geometry removed" << logEndl;
}


void Engine::SingleVertexObject::deinitGLShaders()
{
	_shader.release();
}


void Engine::SingleVertexObject::draw(const glm::mat4x4& mat)
{
	glUseProgram(_shader->getProgram());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&mat[0][0]);

	const glm::vec3& pos = _mesh->getPosition();
	glUniform4f(_attrObjCenterPosition, pos.x, pos.y, pos.z, 1.0f);
	_shader->prepareForRender();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glCBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glUseProgram(0);
}
