#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__


#include <sharedpointer.h>
#include "opengls.hpp"
#include "object.hpp"


class Camera : public Object
{
	public:
		// Static fields.
		static const float DEFAULT_FOV;
		static const float DEFAULT_LOW_DISTANCE;
		static const float DEFAULT_HIGH_DISTANCE;
		static const size_t DEFAULT_WIDTH;
		static const size_t DEFAULT_HEIGHT;

		// Constructors / Destructor.
		Camera();
		Camera(const Camera& c);
		Camera(Camera&& c);
		~Camera();

		// Operators.
		Camera& operator=(const Camera& c);
		Camera& operator=(Camera&& c);

		operator bool() const;
		bool operator!() const;
		bool isValid() const;

		// Methods.
		const float& getFOV() const;
		const float& getLowDistance() const;
		const float& getHighDistance() const;
		const size_t& getWidth() const;
		const size_t& getHeight() const;
		const glm::vec3& getLookingAtPosition() const;
		const glm::vec3& getHeadDirection() const;

		void setFOV(const float& fov);
		void setLowDistance(const float& distance);
		void setHighDistance(const float& distance);
		void setWidth(const size_t& width);
		void setHeight(const size_t& height);
		void setLookingAtPosition(const glm::vec3& lookingAtPosition);
		void setHeadDirection(const glm::vec3& headDirection);

		// Overriden methods.
		void setRotation(const glm::vec3& rotation) override;

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	private:
		float _fov;
		float _low_distance;
		float _high_distance;
		size_t _width;
		size_t _height;
		glm::vec3 _lookingAtPosition;
		glm::vec3 _headDirection;
};

using CameraPtr = SharedPointer<Camera>;


#endif // __CAMERA_HPP__
