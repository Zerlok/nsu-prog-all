// -------------- BASIC INCLUDES -------------- //
#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>

// -------------- OpenGL INCLUDES -------------- //
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


double getTimeAngle()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
//	printf("T: %d.%d ---> %f\n", tp.tv_sec, tp.tv_usec, t);
	return ((tp.tv_sec % 10000) * 10) + (tp.tv_usec / 10000) / 10.0;
}


// -------------- OpenGL GLOBALS -------------- //

float width;
float height;

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;

GLuint VBO; // Vertex Buffer Object
GLuint CBO; // Color Buffer Object
GLuint IBO; // Index Buffer Object

GLuint attrConstColor; // ???


// -------------- MY GLOBALS -------------- //

int FACES_NUM;


// -------------- OpenGL FUNCTIONS -------------- //

void initGeometry()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	FACES_NUM = 36;
	GLuint faces[] = {
		0, 2, 1,  0, 3, 2,
		5, 6, 7,  5, 7, 4,
		1, 5, 4,  1, 4, 0,
		2, 5, 1,  2, 6, 5,
		3, 6, 2,  3, 7, 6,
		0, 7, 4,  0, 3, 7,
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

	GLfloat colors[] = {
		0.2f, 0.7f, 0.2f, 1.0f,
		0.2f, 0.7f, 0.2f, 1.0f,
		0.7f, 0.7f, 0.2f, 1.0f,
		0.7f, 0.7f, 0.2f, 1.0f,
		0.2f, 0.7f, 0.7f, 1.0f,
		0.2f, 0.7f, 0.7f, 1.0f,
		0.7f, 0.2f, 0.7f, 1.0f,
		0.7f, 0.2f, 0.7f, 1.0f,
	};

	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}


void deinitGeometry()
{
	glDeleteBuffers(sizeof(VBO), &VBO);
	glDeleteBuffers(sizeof(CBO), &CBO);
}


void drawMatrix(const glm::mat4x4& matr)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matr[0][0]);

	glUniform4f(attrConstColor, 3, 3, 3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, FACES_NUM, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


void renderGeometry()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glUseProgram(shaderProgram);

	// Matrix Projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;

	// Init Matrices.
	const double globalAngle = getTimeAngle() / 6.283;
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


// Calls in loop
void renderCycle()
{
	glutPostRedisplay();
}


// Reshapes the window appropriately
void reshape(int w, int h)
{
	width  = w;
	height = h;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;

}


void initShaders()
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

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(vertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(fragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "color");

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(shaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program linkage!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(shaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program validation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	attrConstColor = glGetUniformLocation(shaderProgram, "constColor");
}


void deinitShaders()
{
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(2000, 100);
	glutInitWindowSize(768, 512);
	glutCreateWindow("OpenGL - Solar System Simulation");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error in glewInit, code: (%d), message: %s", err, glewGetErrorString(err));
		return 1;
	}

	glutDisplayFunc(renderGeometry);
	glutReshapeFunc(reshape);
	glutIdleFunc(renderCycle);

	initGeometry();
	initShaders();

	glutMainLoop();

	deinitShaders();
	deinitGeometry();

	return 0;
}
