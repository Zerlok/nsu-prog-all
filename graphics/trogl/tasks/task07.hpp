#ifndef __TASK07_HPP__
#define __TASK07_HPP__


#include "task.hpp"
#include "common/peripherals.hpp"


class CameraController : public Keyboard::KeyListener
{
	public:
		CameraController(const CameraPtr& camera);
		~CameraController();

		void onKeyPressed(const Keyboard::Key& key);
		void onKeyReleased(const Keyboard::Key& key);

	private:
		CameraPtr _camera;
};


class Task07ActionInput : public Task
{
	public:
		Task07ActionInput();
		~Task07ActionInput() {}

	private:
		CameraController* _cameraCntrl;
};


#endif // __TASK07_HPP__
