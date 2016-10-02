#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__


#include "object.hpp"


class Camera : public Object
{
	public:
		static const float DEFAULT_FOV;
		static const float DEFAULT_LOW_DISTANCE;
		static const float DEFAULT_HIGH_DISTANCE;
		static const size_t DEFAULT_WIDTH;
		static const size_t DEFAULT_HEIGHT;

		Camera();
		Camera(const Camera& c);
		Camera(Camera&& c);
		virtual ~Camera();

		Camera& operator=(const Camera& c);
		Camera& operator=(Camera&& c);
		operator bool() const;

		bool isValid() const;

		const float& getFOV() const;
		void setFOV(const float& fov);

		const float& getLowDistance() const;
		void setLowDistance(const float& distance);

		const float& getHighDistance() const;
		void setHighDistance(const float& distance);

		const size_t& getWidth() const;
		void setWidth(const size_t& width);

		const size_t& getHeight() const;
		void setHeight(const size_t& height);

	private:
		float _fov;
		float _low_distance;
		float _high_distance;
		size_t _width;
		size_t _height;
};


#endif // __CAMERA_HPP__
