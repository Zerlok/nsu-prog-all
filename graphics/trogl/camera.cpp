#include "camera.hpp"

#include <logger.hpp>


const float Camera::DEFAULT_FOV = 60.0;
const float Camera::DEFAULT_LOW_DISTANCE = 0.01;
const float Camera::DEFAULT_HIGH_DISTANCE = 100.0;
const size_t Camera::DEFAULT_WIDTH = 640;
const size_t Camera::DEFAULT_HEIGHT = 480;


Camera::Camera()
	: Object(Object::Type::CAMERA),
	  _fov(DEFAULT_FOV),
	  _low_distance(DEFAULT_LOW_DISTANCE),
	  _high_distance(DEFAULT_HIGH_DISTANCE),
	  _width(DEFAULT_WIDTH),
	  _height(DEFAULT_HEIGHT),
	  _lookingAtPosition(Object::DEFAULT_POSITION),
	  _headDirection(Object::AXIS_Y)
{
}


Camera::Camera(const Camera& c)
	: Object(c),
	  _fov(c._fov),
	  _low_distance(c._low_distance),
	  _high_distance(c._high_distance),
	  _width(c._width),
	  _height(c._height),
	  _lookingAtPosition(c._lookingAtPosition),
	  _headDirection(c._headDirection)
{
}


Camera::Camera(Camera&& c)
	: Object(std::move(c)),
	  _fov(std::move(c._fov)),
	  _low_distance(std::move(c._low_distance)),
	  _high_distance(std::move(c._high_distance)),
	  _width(std::move(c._width)),
	  _height(std::move(c._height)),
	  _lookingAtPosition(std::move(c._lookingAtPosition)),
	  _headDirection(std::move(c._headDirection))
{
}


Camera::~Camera()
{
}


Camera& Camera::operator=(const Camera& c)
{
	Object::operator=(c);
	_fov = c._fov;
	_low_distance = c._low_distance;
	_high_distance = c._high_distance;
	_width = c._width;
	_height = c._height;
	_lookingAtPosition = c._lookingAtPosition;
	_headDirection = c._headDirection;

	return (*this);
}


Camera& Camera::operator=(Camera&& c)
{
	Object::operator=(c);
	_fov = std::move(c._fov);
	_low_distance = std::move(c._low_distance);
	_high_distance = std::move(c._high_distance);
	_width = std::move(c._width);
	_height = std::move(c._height);
	_lookingAtPosition = std::move(c._lookingAtPosition);
	_headDirection = std::move(c._headDirection);

	return (*this);
}


Camera::operator bool() const
{
	return isValid();
}


bool Camera::operator!() const
{
	return (!bool(*this));
}


bool Camera::isValid() const
{
	// Check fov.
	if ((_fov <= 0.0f)
			&& (_fov >= 170.0))
	{
		logWarning << "Camera: Invalid FOV parameter "
				   << _fov << " (0.0; 170)!" << logEnd;
		return false;
	}

	// Check far and near distances ranges.
	if (_high_distance < _low_distance)
	{
		logWarning << "Camera: Invalid distances parameters: "
				   << _low_distance << " >= " << _high_distance
				   << " (but must be less)" << logEnd;
		return false;
	}

	// Check looking at position distance is in far and near distances range.
	const glm::vec3::length_type lookingDistance = (_lookingAtPosition - _position).length();
	if ((lookingDistance > _high_distance)
			|| (lookingDistance < _low_distance))
	{
		logWarning << "Camera: Invalid looking at distance: "
				   << lookingDistance << " is not in range of [low distance, high distance]"
				   << logEnd;
		return false;
	}

	return true;
}


const float& Camera::getFOV() const
{
	return _fov;
}


void Camera::setFOV(const float& fov)
{
	_fov = fov;
}


const size_t& Camera::getWidth() const
{
	return _width;
}


void Camera::setWidth(const size_t& width)
{
	_width = width;
}


const size_t& Camera::getHeight() const
{
	return _height;
}


void Camera::setHeight(const size_t& height)
{
	_height = height;
}

const glm::vec3& Camera::getLookingAtPosition() const
{
    return _lookingAtPosition;
}

void Camera::setLookingAtPosition(const glm::vec3& lookingAtPosition)
{
    _lookingAtPosition = lookingAtPosition;
}

const glm::vec3& Camera::getHeadDirection() const
{
    return _headDirection;
}

void Camera::setHeadDirection(const glm::vec3& headDirection)
{
    _headDirection = headDirection;
}


const float& Camera::getLowDistance() const
{
    return _low_distance;
}


void Camera::setLowDistance(const float& distance)
{
    _low_distance = distance;
}


const float& Camera::getHighDistance() const
{
	return _high_distance;
}


void Camera::setHighDistance(const float& distance)
{
	_high_distance = distance;
}
