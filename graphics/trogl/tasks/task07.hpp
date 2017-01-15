#ifndef __TASK07_HPP__
#define __TASK07_HPP__


#include "task.hpp"
#include "common/peripherals.hpp"


class CameraController
{
	public:
		class KBListener : public Keyboard::KeyListener
		{
			public:
				KBListener(const CameraPtr& cam);

				void onKeyPressed(const Keyboard::Key& key);
				void onKeyReleased(const Keyboard::Key& key);

			private:
				CameraPtr _camera;
		};

		class MListener : public Mouse::Listener
		{
			public:
				MListener(const CameraPtr& cam);

				void onPerformed(const Mouse::ClickEvent& click) override;

			private:
				CameraPtr _camera;
		};

		CameraController(const CameraPtr& camera);
		~CameraController() {}

		KBListener* getKBListener();
		MListener* getMListener();

	private:
		KBListener* _kb;
		MListener* _m;
};


class Task07ActionInput : public Task
{
	public:
		Task07ActionInput();
		~Task07ActionInput() {}

	private:
		CameraController _cameraCntrl;
};


#endif // __TASK07_HPP__
