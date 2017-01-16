#include "camera.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


const float Camera::DEFAULT_FOV = 45.0;
const size_t Camera::DEFAULT_WIDTH = 640;
const size_t Camera::DEFAULT_HEIGHT = 480;
const float Camera::DEFAULT_NEAR_DISTANCE = 0.01;
const float Camera::DEFAULT_FAR_DISTANCE = 100.0;


Camera::Camera(const size_t& width,
			   const size_t& height)
	: Object("CAMERA", "Camera"),
	  _fov(DEFAULT_FOV),
	  _width(width),
	  _height(height),
	  _lookingAtPosition(Object::DEFAULT_POSITION),
	  _headDirection(space::xyz::y),
	  _nearDistance(DEFAULT_NEAR_DISTANCE),
	  _farDistance(DEFAULT_FAR_DISTANCE)
{
	_position = {0.0f, 0.0f, 5.0f};
	_regProperties();
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
	_regProperties();
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
	_regProperties();
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


const vec3& Camera::getLookingAtPosition() const
{
	return _lookingAtPosition;
}


const vec3& Camera::getHeadDirection() const
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


void Camera::setLookingAtPosition(const vec3& lookingAtPosition)
{
	_lookingAtPosition = lookingAtPosition;
	const vec3 direction = _lookingAtPosition - _position;
	_rotation = glm::angles(direction);
}


void Camera::setHeadDirection(const vec3& headDirection)
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


void Camera::setPosition(const vec3& position)
{
	_lookingAtPosition += (position - _position);
	Object::setPosition(position);
}


void Camera::setRotation(const vec3& rotation)
{
	Object::setRotation(rotation);
	applyRotation();
}


void Camera::applyPosition()
{
}


void Camera::applyRotation()
{
	const glm::mat4x4 rotM = glm::rotationMatrix(_rotation);
	_lookingAtPosition = _position + vec3(rotM * vec4(_lookingAtPosition - _position, 1.0f));
}


void Camera::_regProperties()
{
	Object::_regProperties();
	_regProperty(_fov);
	_regProperty(_width);
	_regProperty(_height);
	_regProperty(_lookingAtPosition);
	_regProperty(_headDirection);
	_regProperty(_nearDistance);
	_regProperty(_farDistance);
}
