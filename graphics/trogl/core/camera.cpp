#include "camera.hpp"


#include <logger.hpp>


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


const float Camera::DEFAULT_FOV = 60.0;
const size_t Camera::DEFAULT_WIDTH = 640;
const size_t Camera::DEFAULT_HEIGHT = 480;
const float Camera::DEFAULT_NEAR_DISTANCE = 0.01;
const float Camera::DEFAULT_FAR_DISTANCE = 100.0;


Camera::Camera()
	: Object(Object::Type::CAMERA),
	  _fov(DEFAULT_FOV),
	  _width(DEFAULT_WIDTH),
	  _height(DEFAULT_HEIGHT),
	  _lookingAtPosition(Object::DEFAULT_POSITION),
	  _headDirection(Object::AXIS_Y),
	  _nearDistance(DEFAULT_NEAR_DISTANCE),
	  _farDistance(DEFAULT_FAR_DISTANCE)
{
	logDebug << "Camera " << getName() << " created." <<logEndl;
}


Camera::Camera(const Camera& cam)
	: Object(cam),
	  _fov(cam._fov),
	  _width(cam._width),
	  _height(cam._height),
	  _lookingAtPosition(cam._lookingAtPosition),
	  _headDirection(cam._headDirection),
	  _nearDistance(cam._nearDistance),
	  _farDistance(cam._farDistance)
{
	logDebug << "Camera " << getName()
			 << " copied from " << cam.getName()
			 << logEndl;
}


Camera::Camera(Camera&& c)
	: Object(std::move(c)),
	  _fov(std::move(c._fov)),
	  _width(std::move(c._width)),
	  _height(std::move(c._height)),
	  _lookingAtPosition(std::move(c._lookingAtPosition)),
	  _headDirection(std::move(c._headDirection)),
	  _nearDistance(std::move(c._nearDistance)),
	  _farDistance(std::move(c._farDistance))
{
	logDebug << "Camera " << getName() << " moved." << logEndl;
}


Camera::~Camera()
{
	logDebug << "Camera " << getName() << " deleted." << logEndl;
}


Camera& Camera::operator=(const Camera& cam)
{
	Object::operator=(cam);
	_fov = cam._fov;
	_width = cam._width;
	_height = cam._height;
	_lookingAtPosition = cam._lookingAtPosition;
	_headDirection = cam._headDirection;
	_nearDistance = cam._nearDistance;
	_farDistance = cam._farDistance;

	logDebug << "Camera " << getName()
			 << " copied from " << cam.getName()
			 << logEndl;
	return (*this);
}


Camera& Camera::operator=(Camera&& cam)
{
	Object::operator=(cam);
	_fov = std::move(cam._fov);
	_width = std::move(cam._width);
	_height = std::move(cam._height);
	_lookingAtPosition = std::move(cam._lookingAtPosition);
	_headDirection = std::move(cam._headDirection);
	_nearDistance = std::move(cam._nearDistance);
	_farDistance = std::move(cam._farDistance);

	logDebug << "Camera " << getName() << " moved." << logEndl;
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
				   << _fov << " (0.0; 170)!" << logEndl;
		return false;
	}

	// Check far and near distances ranges.
	if (_farDistance < _nearDistance)
	{
		logWarning << "Camera: Invalid distances parameters: "
				   << _nearDistance << " >= " << _farDistance
				   << " (but must be less)" << logEndl;
		return false;
	}

	// Check looking at position distance is in far and near distances range.
	const glm::vec3::length_type lookingDistance = (_lookingAtPosition - _position).length();
	if ((lookingDistance > _farDistance)
			|| (lookingDistance < _nearDistance))
	{
		logWarning << "Camera: Invalid looking at distance: "
				   << lookingDistance << " is not in range of [low distance, high distance]"
				   << logEndl;
		return false;
	}

	return true;
}


const float& Camera::getFOV() const
{
	return _fov;
}


const size_t& Camera::getWidth() const
{
	return _width;
}


const size_t& Camera::getHeight() const
{
	return _height;
}


float Camera::getWHRatio() const
{
	return (float(_width)/float(_height));
}


const Object::vec& Camera::getLookingAtPosition() const
{
	return _lookingAtPosition;
}


const Object::vec& Camera::getHeadDirection() const
{
	return _headDirection;
}


const float& Camera::getNearDistance() const
{
	return _nearDistance;
}


const float& Camera::getFarDistance() const
{
	return _farDistance;
}


void Camera::setFOV(const float& fov)
{
	_fov = fov;
}


void Camera::setWidth(const size_t& width)
{
	_width = width;
}


void Camera::setHeight(const size_t& height)
{
	_height = height;
}


void Camera::setLookingAtPosition(const Object::vec& lookingAtPosition)
{
	// TODO: Rotate camera in direction of lookingAtPosition.
    _lookingAtPosition = lookingAtPosition;
}


void Camera::setHeadDirection(const Object::vec& headDirection)
{
	_headDirection = headDirection;
}


void Camera::setNearDistance(const float& distance)
{
	_nearDistance = distance;
}


void Camera::setFarDistance(const float& distance)
{
	_farDistance = distance;
}


void Camera::setRotation(const Object::vec& rotation)
{
	// TODO: Rotate lookingAtPosition.
	Object::setRotation(rotation);
}


void Camera::applyPosition()
{
}


void Camera::applyRotation()
{
}


void Camera::applyScale()
{
}
