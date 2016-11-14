#include "engine.hpp"


#include <sstream>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::DEBUG,
										 loggerDescriptionFull);


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
	  _camera(nullptr)
{
	logDebug << "Engine created." << logEndl;
}


Engine::~Engine()
{
//	if ((_wasValidated)
//			&& (_glWindow))
//		glutDestroyWindow(_glWindow);

	logDebug << "Engine removed." << logEndl;
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
			<< polygonsNum << " polygons)"
			<< logEndl;
}


int Engine::_validateScene()
{
	if (!_scene)
	{
		logError << "Cannot show scene - it was not set yet!" << logEndl;
		return 0;
	}

	_camera = _scene->getCamera();
	if (!_camera->isValid())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " with camera " << _camera->getName()
				 << " which settings are invalid!" << logEndl;
		return 0;
	}

	if (_scene->getLights().empty())
		logWarning << "No lamps found at scene " << _scene->getName()
				   << logEndl;

	return 1;
}


int Engine::_validateFrame()
{
	_frame = new Frame(_generateWindowTitle(*_scene),
					   _camera->getWidth(),
					   _camera->getHeight());

	return (_frame->validate()) ? 1 : 0;
}


int Engine::_validateMeshes()
{
	for (const MeshPtr& mesh : _scene->getMeshes())
	{
		_objects.push_back({mesh});
		VertexObject& obj = _objects.back();
		obj.initGLGeometry();
		obj.compileGLShaders();

		if (!obj.isValid())
		{
			logWarning << "Invalid object " << mesh->getName()
					   << " will not be rendered." << logEndl;
			_objects.pop_back();
		}
	}

	if (_objects.empty())
	{
		logError << "None valid mesh found in scene " << _scene->getName() << logEndl;
		return 0;
	}

	return 1;
}


void Engine::_enableGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);

	glPolygonMode(GL_FRONT_AND_BACK, _glRenderMode);
}


void Engine::_initGLProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_camera->getFOV(),
				   _camera->getWHRatio(),
				   _camera->getNearDistance(),
				   _camera->getFarDistance());
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


const Engine::Status&Engine::getStatus() const
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
	_gui = gui;
}


void Engine::setActiveScene(const ScenePtr& scene)
{
	_status = Status::DIRTY;
	_scene = scene;
}


void Engine::setRenderMode(const Engine::RenderMode& mode)
{
	_glRenderMode = mode;
}


bool Engine::validate()
{
	int result = 0;
	result += _validateScene();
	result += _validateFrame();
	result += _validateMeshes();

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

	_logSceneStatistics();
	_status = Status::RENDERING_STARTED;

	_enableGLOptions();
	_initGLProjectionMatrix();
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

	if (_guiFPS)
	{
		_guiFPS->tick();
		_guiFPS->draw(width, height);
	}

	if (_gui)
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

	// TODO: use one style matricies coding (OpenGL).
	glm::mat4x4 matView = glm::lookAt(_camera->getPosition(),
									  _camera->getLookingAtPosition(),
									  _camera->getHeadDirection());
	// TODO: move into animation.
//	matView = glm::rotate(matView, 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	matView = glm::rotate(matView, float(getTimeDouble() / 31.0), glm::vec3(0.0f, 1.0f, 0.0f));
//	matView = glm::rotate(matView, float(getTimeDouble() / 17.0), glm::vec3(0.0f, 0.0f, 1.0f));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matView[0][0]);

	for (VertexObject& obj : _objects)
		for (const LightPtr& light : _scene->getLights())
			obj.draw(light);

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
}


void Engine::_idleFunc()
{
	glutPostRedisplay();
}


void Engine::_reshapeFunc(int width, int height)
{
	instance()._reshape(width, height);
}


std::string Engine::_generateWindowTitle(const Scene& scene)
{
	std::stringstream ss;
	ss << "TroGL Engine [" << scene.getName() << ']';
	return ss.str();
}


// --------------------- SINGLE VERTEX OBJECT --------------------- //

const size_t Engine::VertexObject::_vertexStep = 4;
const size_t Engine::VertexObject::_colorStep = 4;
const size_t Engine::VertexObject::_indexStep = 3;


Engine::VertexObject::VertexObject(const MeshPtr& mesh)
	: _glVBO(0),
	  _glNBO(0),
	  _glCBO(0),
	  _glIBO(0),
	  _indicesSize(0),
	  _shader(mesh->getMaterial()->getShader()),
	  _mesh(mesh)
{
	/*
	 * Apply mesh vertices positions from object attributes
	 * (in reverse order: scale, rotation, position).
	 */
	Object::vec meshPos = _mesh->getPosition();

	_mesh->recalculateNormals();
	_mesh->applyScale();
	_mesh->applyRotation();
	_mesh->applyPosition();

	_mesh->setPosition(meshPos);
}


Engine::VertexObject::VertexObject(Engine::VertexObject&& obj)
	: _glVBO(std::move(obj._glVBO)),
	  _glNBO(std::move(obj._glNBO)),
	  _glCBO(std::move(obj._glCBO)),
	  _glIBO(std::move(obj._glIBO)),
	  _indicesSize(std::move(obj._indicesSize)),
	  _shader(std::move(obj._shader)),
	  _mesh(std::move(obj._mesh))
{
	obj._glVBO = 0;
	obj._glNBO = 0;
	obj._glCBO = 0;
	obj._glIBO = 0;
}


Engine::VertexObject::~VertexObject()
{
	_deinitGLGeometry();
}


bool Engine::VertexObject::isValid() const
{
	return (_isGLGeometryValid()
			&& _shader->isCompiledSuccessfuly());
}


void Engine::VertexObject::initGLGeometry()
{
	if (_isGLGeometryValid())
		return;

	_initVertexBufferObject();
	_initColorBufferObject();
	_initIndexBufferObject();
}


void Engine::VertexObject::compileGLShaders()
{
	_shader->compile();
}


void Engine::VertexObject::draw(const LightPtr& light)
{
	_shader->use();
	_shader->passObject(_mesh.get_pointer());
	_shader->passObject(light.get_pointer());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glVertexAttribPointer(0, _vertexStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glNBO);
	glVertexAttribPointer(1, _vertexStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _glCBO);
	glVertexAttribPointer(2, _colorStep, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glDrawElements(GL_TRIANGLES, _indicesSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


bool Engine::VertexObject::_isGLGeometryValid() const
{
	return ((_glVBO != 0)
			&& (_glNBO != 0)
			&& (_glCBO != 0)
			&& (_glIBO != 0));
}


void Engine::VertexObject::_initVertexBufferObject()
{
	std::vector<GLfloat> vertices((_mesh->getVertices().size() * _vertexStep), 0.0f);
	std::vector<GLfloat> normals((_mesh->getVertices().size() * _vertexStep), 0.0f);
	size_t idx = 0;

	for (size_t i = 0; i < vertices.size(); i += _vertexStep)
	{
		const Mesh::Vertex& v = _mesh->getVertex(idx++);

		vertices[i] = v.getPosition().x;
		vertices[i+1] = v.getPosition().y;
		vertices[i+2] = v.getPosition().z;
		vertices[i+3] = 1.0f;

		normals[i] = v.getNormal().x;
		normals[i+1] = v.getNormal().y;
		normals[i+2] = v.getNormal().z;
		normals[i+3] = 0.0f;
	}

	glGenBuffers(1, &_glVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_glNBO);
	glBindBuffer(GL_ARRAY_BUFFER, _glNBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
}


void Engine::VertexObject::_initColorBufferObject()
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


void Engine::VertexObject::_initIndexBufferObject()
{
	std::vector<GLuint> indicies((_mesh->getPolygons().size() * _indexStep), 0.0f);
	size_t i = 0;

	// TODO: get indicies from mesh method, which knows their order and indexing type.
	for (const Mesh::Polygons::value_type& pair : _mesh->getPolygons())
	{
		const Mesh::Polygon& poly = pair.second;
		indicies[i++] = poly.getIdx1();
		indicies[i++] = poly.getIdx2();
		indicies[i++] = poly.getIdx3();
	}
	_indexType = _mesh->getIndexType();
	_indicesSize = indicies.size() * sizeof(GLuint);

	glGenBuffers(1, &_glIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, indicies.data(), GL_STATIC_DRAW);
}


void Engine::VertexObject::_deinitGLGeometry()
{
	if (_isGLGeometryValid())
		logDebug << "Removing object's geometry" << logEndl;

	if (_glVBO != 0)
		glDeleteBuffers(sizeof(_glVBO), &_glVBO);

	if (_glNBO != 0)
		glDeleteBuffers(sizeof(_glNBO), &_glNBO);

	if (_glCBO != 0)
		glDeleteBuffers(sizeof(_glCBO), &_glCBO);

	if (_glIBO != 0)
		glDeleteBuffers(sizeof(_glIBO), &_glIBO);
}


Frame::Frame(const std::string& title,
			 const size_t& width,
			 const size_t& height)
	: _title(title),
	  _width(width),
	  _height(height)
{
	int argc = 1;
	char* argv[1] = {"engine"};

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutInitWindowSize(_width, _height);
	_glWindow = glutCreateWindow(_title.c_str());
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

	return true;
}


void Frame::resize(const size_t& width,
				   const size_t& height)
{
	_width = width;
	_height = height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}


void Frame::clear(const Color& color)
{
	// TODO: add comment description: what does each line do with GL.
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
