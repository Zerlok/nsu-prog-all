#include "opengls.hpp"


#include <iomanip>
#include <utility>


static const int precPoint = 3;


glm::vec2 glm::operator*(const float& val, const glm::vec2& vec)
{
	glm::vec2 tmp(vec);
	tmp *= val;
	return std::move(tmp);
}


glm::vec2 glm::operator*(const glm::vec2& vec, const float& val)
{
	glm::vec2 tmp(vec);
	tmp *= val;
	return std::move(tmp);
}


glm::vec2 glm::operator+(const glm::vec2& val1, const glm::vec2& val2)
{
	glm::vec2 tmp(val1);
	tmp += val2;
	return std::move(tmp);
}


glm::vec3 glm::operator*(const float& val, const glm::vec3& vec)
{
	glm::vec3 tmp(vec);
	tmp *= val;
	return std::move(tmp);
}


glm::vec3 glm::operator*(const glm::vec3& vec, const float& val)
{
	glm::vec3 tmp(vec);
	tmp *= val;
	return std::move(tmp);
}


glm::vec3 glm::operator+(const glm::vec3& val1, const glm::vec3& val2)
{
	glm::vec3 tmp(val1);
	tmp += val2;
	return std::move(tmp);
}


std::ostream& glm::operator<<(std::ostream& out, const glm::vec2& v)
{
	out << "vec2("
		<< std::setprecision(precPoint) << v.x << ", "
		<< std::setprecision(precPoint) << v.y << ')';
	return out;
}


std::ostream& glm::operator<<(std::ostream& out, const glm::vec3& v)
{
	out << "vec3("
		<< std::setprecision(precPoint) << v.x << ", "
		<< std::setprecision(precPoint) << v.y << ", "
		<< std::setprecision(precPoint) << v.z << ')';
	return out;
}


float glm::angle(const float& acos, const float& asin)
{
	if ((asin < 0.0f)
			&& (acos < 0.0f))
		return acos + half_pi<float>();

	else if ((asin < 0.0f)
			 && (acos >= 0.0f))
		return two_pi<float>() - acos;

	else if ((asin >= 0.0f)
			 && (acos < 0.0f))
		return pi<float>() - acos;

	else
		return acos;
}


glm::vec3 glm::angles(const glm::vec3& v)
{
	const glm::vec3 tmp = glm::normalize(v);
	const float y = std::acos(tmp.y);
	const float x1 = std::acos(tmp.x);
	const float z1 = std::acos(tmp.z);
	const float x2 = std::asin(tmp.z);
	const float z2 = std::asin(tmp.x);

	return {angle(x1, x2), y, angle(z1, z2)};
}


glm::mat4x4 glm::rotationMatrix(const glm::vec3& angles)
{
	return std::move(glm::rotate(matrix::identic::m4x4, angles.z, space::xyz::z)
					 * glm::rotate(matrix::identic::m4x4, angles.x, space::xyz::x)
					 * glm::rotate(matrix::identic::m4x4, angles.y, space::xyz::y));
}
