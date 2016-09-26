#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


double getTimeAngle()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	double t = ((tp.tv_sec % 10000) * 10) + (tp.tv_usec / 10000) / 10.0;
	printf("T: %d.%d ---> %f\n", tp.tv_sec, tp.tv_usec, t);
	return t;
}


float width;
float height;

GLuint vertexShader;
GLuint fragmentShader;
GLuint program;

GLuint bufferPosition;
GLuint bufferColor;

GLuint attrConstColor;

int VERTICES_NUM;


void InitGeometry()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,
		1.0f,  1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f,  1.0f, 1.0f, 1.0f,
	};
	VERTICES_NUM = 8;

	glGenBuffers(1, &bufferPosition);
	glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLfloat colors[] = {
		1.0, 0.0, 0.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,
		1.0, 0.0, 1.0, 1.0f,
		0.0, 1.0, 1.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		1.0, 0.0, 1.0, 1.0f,
	};

	glGenBuffers(1, &bufferColor);
	glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}


void DeinitGeometry()
{
	glDeleteBuffers(sizeof(bufferPosition), &bufferPosition);
	glDeleteBuffers(sizeof(bufferColor), &bufferColor);
}


void draw(const glm::mat4x4& matr, const int& begin, const int& end)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matr[0][0]);

	glUniform4f(attrConstColor, 3, 3, 3, 1);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, begin, end);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


void Render (void)
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // Clear the background of our window to red
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glUseProgram(program);

	// Matrix Projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;

	// Init Matrices.
	const double globalAngle = getTimeAngle() / 6.283;
	const glm::mat4x4 matView  = glm::lookAt(glm::vec3(30, 20, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	const glm::mat4x4 matWorld = glm::mat4x4();
	const glm::mat4x4 matWorldView = matView * matWorld;

	// The Sun.
	float aSun = globalAngle;
	const glm::mat4x4 matSunWorldView = glm::rotate(matWorldView, aSun, glm::vec3(0.0f, 1.0f, 0.0f));

	// The Earth.
	float aEarth = globalAngle / 3.0;
	glm::mat4x4 matEarthWorldView = matSunWorldView;
	matEarthWorldView = glm::translate(matEarthWorldView, glm::vec3(10.0f, 0.0f, 0.0f));
	matEarthWorldView = glm::rotate(matEarthWorldView, aEarth, glm::vec3(0.0f, 1.0f, 0.0f));
	matEarthWorldView = glm::scale(matEarthWorldView, glm::vec3(0.5f, 0.5f, 0.5f));

	// The Moon.
	float aMoon = globalAngle / 9.0;
	glm::mat4x4 matMoonWorldView = matEarthWorldView;
	matMoonWorldView = glm::translate(matMoonWorldView, glm::vec3(5.0f, 0.0f, 0.0f));
	matMoonWorldView = glm::rotate(matMoonWorldView, aMoon, glm::vec3(0.0f, 1.0f, 0.0f));
	matMoonWorldView = glm::scale(matMoonWorldView, glm::vec3(0.5f, 0.5f, 0.5f));

	// Drawing.
	draw(matMoonWorldView, 0, VERTICES_NUM);
	draw(matEarthWorldView, 0, VERTICES_NUM);
	draw(matSunWorldView, 0, VERTICES_NUM);

	// In the end.
	glUseProgram(0);
	glFlush();
}


// Calls in loop
void Cycle()
{
	double angle = getTimeAngle();
//	printf("A: %f\n", angle);
	glutPostRedisplay();
}


// Reshapes the window appropriately
void Reshape(int w, int h)
{
	width  = w;
	height = h;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;

}


void InitShaders()
{
	//! Čńőîäíűé ęîä řĺéäĺđîâ
	const char* vsSource =
		//"attribute vec3 coord;\n"
		//"out vec3 fragmentColor;\n"
		"attribute vec4 position;"
		"attribute vec4 color;"
		"uniform vec4 constColor;"
		"void main() {\n"
		//"  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
		//"  gl_FrontColor = gl_Color;\n"
		"  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
		"  gl_FrontColor = color * constColor;\n"
		"}\n";
	const char* fsSource =
		//"uniform vec4 color;\n"
		//"in vec3 fragmentColor;\n"
		"void main() {\n"
		//"  gl_FragColor = color;\n"
		"  gl_FragColor = gl_Color;\n"
		//"  gl_FragColor = vec4(fragmentColor, 1.0);\n"
		"}\n";
	int success = 0;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (vertexShader, 1, &vsSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv  (vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(vertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource (fragmentShader, 1, &fsSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv  (fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(fragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");

	glLinkProgram (program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program linkage!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program validation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	attrConstColor = glGetUniformLocation(program, "constColor");
}


void DeinitShaders()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteProgram(program);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_RGBA);
	//glEnable(GL_DEPTH_TEST);
	// Create the application's window
	{
		glutInitWindowPosition(2000, 100);			// Set the position of the window
		glutInitWindowSize(768, 512);				// Set the width and height of the window
		glutCreateWindow("OpenGL First Window");	// Set the title for the window
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error in glewInit, code: (%d), message: %s", err, glewGetErrorString(err));
		return 1;
	}
	else
		fprintf(stdout, "Running the application...\n");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Cycle);

	InitGeometry();
	InitShaders();

	glutMainLoop();

	DeinitShaders();

	int i = 0;

	return 0;
}
