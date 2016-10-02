#include "engine.hpp"

#include <logger.hpp>
#include <sstream>
#include "common/utils.h"


TroglEngine* TroglEngine::_current = nullptr;


TroglEngine::TroglEngine()
	: _width(0),
	  _height(0),
	  _vertexShader(),
	  _fragmentShader(),
	  _shaderProgram(),
	  _vbo_size(0),
	  _cbo_size(0),
	  _ibo_size(0),
	  _vbo(),
	  _cbo(),
	  _ibo(),
	  _attrConstColor()
{
	logDebug << "Engine init started" << logEnd;

	logDebug << "Engine created" << logEnd;
}


TroglEngine::~TroglEngine()
{
	if (_isValid)
	{
		deinitShaders();
		deinitGeometry();
	}

	logDebug << "Engine removed" << logEnd;
}


void TroglEngine::showScene(const Scene& scene)
{
	int argc = 1;
	char* argv = "engine";
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(2000, 100);
	glutInitWindowSize(
				scene.getCamera().getWidth(),
				scene.getCamera().getHeight());
	glutCreateWindow(generateWindowName(scene).c_str());
	_isValid = runGlewTest();

	if (!_isValid)
	{
		logError << "Cannot show scene " << scene.getName()
				 << " engine couldn't initialize" << logEnd;
		return;
	}

	logInfo << "Engine rendering started (scene: "
			<< scene.getName() << ")" << logEnd;

	_current = this;
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutIdleFunc(renderCycle);

	// TODO: add scene lamps.

	// TODO: add scene meshes.
	for (const Mesh& m : scene.getMeshes())
		initGeometry(m);

//	initGeometry();
	initShaders();

	glutMainLoop();
}


void renderCycle()
{
	glutPostRedisplay();
}


void TroglEngine::reshape(int w, int h)
{
	float& width = _current->_width;
	float& height = _current->_height;

	width = w;
	height = h;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;
}


void TroglEngine::drawMatrix(const glm::mat4x4& mat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&mat[0][0]);

	glUniform4f(_attrConstColor, 3, 3, 3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glDrawElements(GL_TRIANGLES, _ibo_size, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


void TroglEngine::initGeometry(const Mesh& mesh)
{
	_ibo_size = mesh.getFaces().size() * 3 * sizeof(GLuint);
	_vbo_size = mesh.getVertices().size() * 4 * sizeof(GLfloat);
	_cbo_size = _vbo_size;

	GLfloat* vertices = new GLfloat[_vbo_size];
	GLfloat* colors = new GLfloat[_cbo_size];
	GLuint* indicies = new GLuint[_ibo_size];

	size_t idx = 0;
	for (size_t i = 0; i < _vbo_size; i += 4)
	{
		const Mesh::Vertex& v = mesh.getVertex(idx);
		++idx;

		vertices[i] = v.getPosition().getX();
		vertices[i+1] = v.getPosition().getY();
		vertices[i+2] = v.getPosition().getZ();
		vertices[i+3] = 1.0f;

		colors[i] = v.getColor().getRedF();
		colors[i+1] = v.getColor().getGreenF();
		colors[i+2] = v.getColor().getBlueF();
		colors[i+3] = v.getColor().getAlphaF();
	}

	idx = 0;
	for (size_t i = 0; i < _ibo_size; i += 3)
	{
		const Mesh::Face& f = mesh.getFace(idx);
		++idx;

		indicies[i] = f.getFirstIndex();
		indicies[i+1] = f.getSecondIndex();
		indicies[i+2] = f.getThirdIndex();
	}

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vbo_size, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _ibo_size, indicies, GL_STATIC_DRAW);

	glGenBuffers(1, &_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glBufferData(GL_ARRAY_BUFFER, _cbo_size, colors, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] colors;
	delete[] indicies;
}


void TroglEngine::drawGeometry()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glUseProgram(_shaderProgram);

	// Matrix Projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)_width/(GLdouble)_height, 0.01, 100.0) ;

	// Init Matrices.
	const double globalAngle = getTime() / 6.283;
	const glm::mat4x4 matView  = glm::lookAt(glm::vec3(20, 13, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	const glm::mat4x4 matWorld = glm::mat4x4();
	const glm::mat4x4 matWorldView = matView * matWorld;

	// The Sun.
	const float aSun = globalAngle / 2.0;
	const float aSunEarth = globalAngle / 3.0;
	const glm::mat4x4 matSunWorld = glm::rotate(matWorldView, aSunEarth, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4x4 matSunWorldView = glm::rotate(matWorldView, aSun, glm::vec3(0.0f, 1.0f, 0.0f));
	matSunWorldView = glm::rotate(matSunWorldView, aSun / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	// The Earth.
	const float aEarth = globalAngle * 1.2;
	const float aEarthMoon = globalAngle * 0.9;
	glm::mat4x4 matEarthWorld = matSunWorld;
	matEarthWorld = glm::translate(matEarthWorld, glm::vec3(10.0f, 0.0f, 0.0f));
	matEarthWorld= glm::scale(matEarthWorld, glm::vec3(0.5f, 0.5f, 0.5f));
	const glm::mat4x4 matEarthWorldView = glm::rotate(matEarthWorld, aEarth, glm::vec3(0.0f, 1.0f, 0.0f));
	matEarthWorld= glm::rotate(matEarthWorld, aEarthMoon, glm::vec3(0.0f, 1.0f, 0.0f));

	// The Moon.
	float aMoon = globalAngle / 9.0;
	glm::mat4x4 matMoonWorldView = matEarthWorld;
	matMoonWorldView = glm::translate(matMoonWorldView, glm::vec3(5.0f, 0.0f, 0.0f));
	matMoonWorldView = glm::rotate(matMoonWorldView, aMoon, glm::vec3(0.0f, 1.0f, 0.0f));
	matMoonWorldView = glm::scale(matMoonWorldView, glm::vec3(0.3f, 0.3f, 0.3f));

	// Drawing.
	drawMatrix(matMoonWorldView);
	drawMatrix(matEarthWorldView);
	drawMatrix(matSunWorldView);

	// In the end.
	glUseProgram(0);
	glFlush();
}


void TroglEngine::deinitGeometry()
{
	glDeleteBuffers(sizeof(_vbo), &_vbo);
	glDeleteBuffers(sizeof(_ibo), &_ibo);
	glDeleteBuffers(sizeof(_vbo), &_cbo);
}


void TroglEngine::initShaders()
{
	const char* vsSource =
		"attribute vec4 position;"
		"attribute vec4 color;"
		"uniform vec4 constColor;"
		"void main() {\n"
		"  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
		"  gl_FrontColor = color * constColor;\n"
		"}\n";
	const char* fsSource =
		"void main() {\n"
		"  gl_FragColor = gl_Color;\n"
		"}\n";
	int success = 0;

	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &vsSource, NULL);
	glCompileShader(_vertexShader);
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_vertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &fsSource, NULL);
	glCompileShader(_fragmentShader);
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_fragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);

	glBindAttribLocation(_shaderProgram, 0, "position");
	glBindAttribLocation(_shaderProgram, 1, "color");

	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(_shaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program linkage!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	glValidateProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(_shaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program validation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	_attrConstColor = glGetUniformLocation(_shaderProgram, "constColor");
}


void TroglEngine::deinitShaders()
{
	glDetachShader(_shaderProgram, _vertexShader);
	glDetachShader(_shaderProgram, _fragmentShader);
	glDeleteProgram(_shaderProgram);
	glDeleteShader(_fragmentShader);
	glDeleteShader(_vertexShader);
}


void TroglEngine::draw()
{
	_current->drawGeometry();
}


std::string TroglEngine::generateWindowName(const Scene& scene)
{
	std::stringstream ss;
	ss << "Trogl Engine [" << scene.getName() << "]";
	return ss.str();
}


bool TroglEngine::runGlewTest() const
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		logError << "Error in glewInit, code: " << err
				 << ", message: " << glewGetErrorString(err) << logEnd;
		return false;
	}

	return true;
}
