#ifndef __OPENGLS_HPP__
#define __OPENGLS_HPP__


/*
 * This is a right order of including OpenGLs' headers.
 * DO NOT CHANGE IT, WHATEVER! Even if I've told you.
 *
 * Linux OpenGL installation:
 *    - https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Linux
 *    - $ sudo apt-get install freeglut3 freeglut3-dev
 */
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace glm
{
	glm::vec2 operator*(const float& val, const glm::vec2& vec);
	glm::vec2 operator*(const glm::vec2& vec, const float& val);
	glm::vec2 operator+(const glm::vec2& val1, const glm::vec2& val2);

	glm::vec3 operator*(const float& val, const glm::vec3& vec);
	glm::vec3 operator*(const glm::vec3& vec, const float& val);
	glm::vec3 operator+(const glm::vec3& val1, const glm::vec3& val2);
}


#endif // __OPENGLS_HPP__
