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


#include <iostream>


namespace glm
{
	glm::vec2 operator*(const float& val, const glm::vec2& vec);
	glm::vec2 operator*(const glm::vec2& vec, const float& val);
	glm::vec2 operator+(const glm::vec2& val1, const glm::vec2& val2);

	glm::vec3 operator*(const float& val, const glm::vec3& vec);
	glm::vec3 operator*(const glm::vec3& vec, const float& val);
	glm::vec3 operator+(const glm::vec3& val1, const glm::vec3& val2);

	std::ostream& operator<<(std::ostream& out, const glm::vec2& v);
	std::ostream& operator<<(std::ostream& out, const glm::vec3& v);
	std::ostream& operator<<(std::ostream& out, const glm::mat4x4& mat);

	float angle(const float& acos, const float& asin);
	glm::vec3 angles(const glm::vec3& v);

	glm::mat4x4 rotationMatrix(const glm::vec3& angles);
}


namespace space
{
	namespace xy
	{
		static const glm::vec2 zero(0.0f, 0.0f);
		static const glm::vec2 identic(1.0f, 1.0f);

		static const glm::vec2 x(1.0f, 0.0f);
		static const glm::vec2 y(0.0f, 1.0f);
	}

	namespace xyz
	{
		static const glm::vec3 zero(0.0f, 0.0f, 0.0f);
		static const glm::vec3 identic(1.0f, 1.0f, 1.0f);

		static const glm::vec3 x(1.0f, 0.0f, 0.0f);
		static const glm::vec3 y(0.0f, 1.0f, 0.0f);
		static const glm::vec3 z(0.0f, 0.0f, 1.0f);
	}
}


namespace matrix
{
	namespace zero
	{
		static const glm::mat2x2 m2x2(0.0f);
		static const glm::mat4x4 m3x3(0.0f);
		static const glm::mat4x4 m4x4(0.0f);
	}

	namespace identic
	{
		static const glm::mat2x2 m2x2(1.0f);
		static const glm::mat4x4 m3x3(1.0f);
		static const glm::mat4x4 m4x4(1.0f);
	}
}


#endif // __OPENGLS_HPP__
