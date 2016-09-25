#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>


const int WINDOW_HEIGHT = 512;
const int WINDOW_WIDTH = 512;
const char* WINDOW_TITLE = "OpenGL running...";


GLuint geometryBuffer;
GLuint colorBuffer;
GLuint program;


static long getTimeNanos()
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}


void renderer()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void reshaper(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;
}


void cycler()
{
//	std::cout << getTimeNanos() << std::endl;
	glutPostRedisplay();
}


void init_geometry()
{
	const float x = 0;
	const float y = 0;
	const float z = 0;
	const float ha = 2;
	GLfloat vertices[] = {
		x-ha, y-ha, z-ha, 1.0f,
		x-ha, y+ha, z-ha, 1.0f,
		x+ha, y-ha, z-ha, 1.0f,
		x+ha, y+ha, z-ha, 1.0f,
		x-ha, y-ha, z+ha, 1.0f,
		x-ha, y+ha, z+ha, 1.0f,
		x+ha, y-ha, z+ha, 1.0f,
		x+ha, y+ha, z+ha, 1.0f,
	};
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};

	glGenBuffers(1, &geometryBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}


void deinit_geometry()
{
}


void init_shaders()
{
}


void deinit_shaders()
{
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutInitWindowPosition(1000, 100);
	glutCreateWindow(WINDOW_TITLE);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Error: " << glewGetErrorString(res) << std::endl;
		return 1;
	}

	glutDisplayFunc(renderer);
	glutReshapeFunc(reshaper);
	glutIdleFunc(cycler);

//	init_geometry();
	init_shaders();

	glutMainLoop();

	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	deinit_shaders();
	deinit_geometry();

	return 0;
}

