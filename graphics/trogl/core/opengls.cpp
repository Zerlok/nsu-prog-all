#include "opengls.hpp"


#include <utility>


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
