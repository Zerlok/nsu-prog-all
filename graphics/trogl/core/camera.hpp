#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__


#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "object.hpp"


class Camera : public Object
{
	public:
		// Static fields.
		static const float DEFAULT_FOV;
		static const size_t DEFAULT_WIDTH;
		static const size_t DEFAULT_HEIGHT;
		static const float DEFAULT_NEAR_DISTANCE;
		static const float DEFAULT_FAR_DISTANCE;

		// Constructors / Destructor.
		Camera(const size_t& width = DEFAULT_WIDTH,
			   const size_t& height = DEFAULT_HEIGHT);
		Camera(const Camera& cam);
		Camera(Camera&& c);
		~Camera();

		// Operators.
		Camera& operator=(const Camera& cam);
		Camera& operator=(Camera&& cam);

		operator bool() const;
		bool operator!() const;
		bool isValid() const;

		// Methods.
		const float& getFOV() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		float getWHRatio() const;
		const vec& getLookingAtPosition() const;
		const vec& getHeadDirection() const;
		const float& getNearDistance() const;
		const float& getFarDistance() const;

		void setFOV(const float& fov);
		void setWidth(const size_t& width);
		void setHeight(const size_t& height);
		void setLookingAtPosition(const vec& lookingAtPosition);
		void setHeadDirection(const vec& headDirection);
		void setNearDistance(const float& distance);
		void setFarDistance(const float& distance);

		// Overriden methods.
		void setPosition(const vec& position) override;
		void setRotation(const vec& rotation) override;

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	private:
		float _fov;
		size_t _width;
		size_t _height;
		vec _lookingAtPosition;
		vec _headDirection;
		float _nearDistance;
		float _farDistance;
};

using CameraPtr = SharedPointer<Camera, Object>;


#endif // __CAMERA_HPP__
