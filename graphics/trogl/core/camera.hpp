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

		Camera& operator+=(const Camera& cam);
		Camera& operator*=(const float& ratio);
		Camera operator+(const Camera& cam) const;
		Camera operator*(const float& ratio) const;

		operator bool() const;
		bool operator!() const;
		bool isValid() const;

		// Methods.
		const float& getFOV() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		float getWHRatio() const;
		const vec3& getLookingAtPosition() const;
		const vec3& getHeadDirection() const;
		const float& getNearDistance() const;
		const float& getFarDistance() const;

		void setFOV(const float& fov);
		void setWidth(const size_t& width);
		void setHeight(const size_t& height);
		void setLookingAtPosition(const vec3& lookingAtPosition);
		void setHeadDirection(const vec3& headDirection);
		void setNearDistance(const float& distance);
		void setFarDistance(const float& distance);

		// Overriden methods.
		void setPosition(const vec3& position) override;
		void setRotation(const vec3& rotation) override;

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	protected:
		void _regProperties() override;

	private:
		float _fov;
		size_t _width;
		size_t _height;
		vec3 _lookingAtPosition;
		vec3 _headDirection;
		float _nearDistance;
		float _farDistance;
};

using CameraPtr = SharedPointer<Camera, Object>;


#endif // __CAMERA_HPP__
