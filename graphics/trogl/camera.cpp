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
	  _height(DEFAULT_HEIGHT)
{
}


Camera::Camera(const Camera& c)
	: Object(c),
	  _fov(c._fov),
	  _low_distance(c._low_distance),
	  _high_distance(c._high_distance),
	  _width(c._width),
	  _height(c._height)
{
}


Camera::Camera(Camera&& c)
	: Object(std::move(c)),
	  _fov(std::move(c._fov)),
	  _low_distance(std::move(c._low_distance)),
	  _high_distance(std::move(c._high_distance)),
	  _width(std::move(c._width)),
	  _height(std::move(c._height))
{
}


Camera::~Camera()
{
}


Camera& Camera::operator=(const Camera& c)
{
	_fov = c._fov;
	_low_distance = c._low_distance;
	_high_distance = c._high_distance;
	_width = c._width;
	_height = c._height;

	return (*this);
}


Camera& Camera::operator=(Camera&& c)
{
	_fov = std::move(c._fov);
	_low_distance = std::move(c._low_distance);
	_high_distance = std::move(c._high_distance);
	_width = std::move(c._width);
	_height = std::move(c._height);

	return (*this);
}


Camera::operator bool() const
{
	return isValid();
}


bool Camera::isValid() const
{
	if ((_fov <= 0.0f)
			&& (_fov >= 170.0))
	{
		logWarning << "Camera: Invalid FOV parameter "
				   << _fov << " (0.0; 170)!" << logEnd;
		return false;
	}

	if (_high_distance < _low_distance)
	{
		logWarning << "Camera: Invalid distances parameters: "
				   << _low_distance << " >= " << _high_distance
				   << " (but must be less)" << logEnd;
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
