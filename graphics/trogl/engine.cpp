#include "engine.hpp"


#include <sstream>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::DEBUG,
										 loggerDescriptionFull);



Engine& Engine::instance()
{
	static Engine e;
	return e;
}


Engine::Engine()
	: _status(),
	  _glWindow(0),
	  _glRenderMode(RenderMode::POLYGONS),
	  _frameWidth(0),
	  _frameHeight(0),
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


bool Engine::isInvalid() const
{
	switch (_status)
	{
		case Status::DIRTY:
		case Status::VALIDATION_FAILED:
			return true;

		case Status::VALIDATION_SUCCESSFUL:
		case Status::RENDERING_STARTED:
		case Status::RENDERING_FINISHED:
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
	_status = Status::VALIDATION_FAILED;

	if (!_scene)
	{
		logError << "Cannot show scene - it was not set yet!" << logEndl;
		return false;
	}

	int argc = 1;
	char* argv = "engine";
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(2000, 100);

	const CameraPtr& cam = _scene->getCamera();
	glutInitWindowSize(
				cam->getWidth(),
				cam->getHeight());
	_glWindow = glutCreateWindow(_generateWindowName(*_scene).c_str());

	if (!_runGlewTest())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " - glut initialization failed!" << logEndl;
		return false;
	}

	if (!cam->isValid())
	{
		logError << "Cannot show scene " << _scene->getName()
				 << " - camera settings are invalid" << logEndl;
		return false;
	}

	// TODO: add light to scene.

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

	_camera = _scene->getCamera();

	_status = Status::VALIDATION_SUCCESSFUL;
	return true;
}


void Engine::showScene()
{
	if (!wasValidated()
			&& !validate())
		return;

	glutDisplayFunc(_displayFunc);
	glutReshapeFunc(_reshapeFunc);
	glutIdleFunc(_idleFunc);

	size_t verticesNum = 0;
	size_t polygonsNum = 0;
	for (const MeshPtr& m : _scene->getMeshes())
	{
		verticesNum += m->getVertices().size();
		polygonsNum += m->getPolygons().size();
	}

	logInfo << "Engine rendering started (scene: " << _scene->getName() << ")" << logEndl;
	logInfo << "Scene has "
			<< _scene->getMeshes().size() << " meshes ("
			<< verticesNum << " vertices, "
			<< polygonsNum << " polygons)"
			<< logEndl;

	_status = Status::RENDERING_STARTED;
	glutMainLoop();
	_status = Status::RENDERING_FINISHED;

	logInfo << "Engine rendering finished." << logEndl;
}


void Engine::drawGUI()
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
	glabel.draw(_frameWidth, _frameHeight);
}


void Engine::drawGUIPlane(const GUIPlane& gplane)
{
}


void Engine::renderFrame()
{
	// TODO: use one style coding (OpenGL)
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

	glPolygonMode(GL_FRONT_AND_BACK, _glRenderMode);

	// Matrix View Projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	_frameWidth = _camera->getWidth();
	_frameHeight = _camera->getHeight();
	gluPerspective(_camera->getFOV(),
				   (GLdouble)_frameWidth/(GLdouble)_frameHeight,
				   _camera->getNearDistance(),
				   _camera->getFarDistance());

	glm::mat4x4 matView = glm::lookAt(_camera->getPosition(),
									  _camera->getLookingAtPosition(),
									  _camera->getHeadDirection());
	// TODO: move into animation.
//	matView = glm::rotate(matView, 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	matView = glm::rotate(matView, float(getTimeDouble() / 31.0), glm::vec3(0.0f, 1.0f, 0.0f));
//	matView = glm::rotate(matView, float(getTimeDouble() / 17.0), glm::vec3(0.0f, 0.0f, 1.0f));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matView[0][0]);

	// Draw the objects.
	for (VertexObject& obj : _objects)
		// TODO: draw object for each light.
		obj.draw(_scene->getLights().front());

	// Draw GUI at the end of frame (to overlay over every objects on scene).
	drawGUI();

	// In the end.
	glFlush();
}


void Engine::_displayFunc()
{
	instance().renderFrame();
}


void Engine::_idleFunc()
{
	glutPostRedisplay();
}


void Engine::_reshapeFunc(int w, int h)
{
	float& width = instance()._frameWidth;
	float& height = instance()._frameHeight;
	const CameraPtr cam = instance()._camera;

	width = w;
	height = h;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cam->getFOV(),
				   (GLdouble)width/(GLdouble)height,
				   cam->getNearDistance(),
				   cam->getFarDistance());
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


std::string Engine::_generateWindowName(const Scene& scene)
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


//Engine::LightObject::LightObject(const LightPtr& light)
//	: _shader(light->getShader())
//{
//}


//Engine::LightObject::LightObject(Engine::LightObject&& obj)
//	: _shader(std::move(obj._shader))
//{
//}


//Engine::LightObject::~LightObject()
//{
//}


//bool Engine::LightObject::isValid() const
//{
//	return _shader->isCompiledSuccessfuly();
//}


//void Engine::LightObject::compileGLShaders()
//{
//	_shader->compile();
//}
