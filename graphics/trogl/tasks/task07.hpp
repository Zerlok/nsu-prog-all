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
				KBListener(CameraController& cntrl);
				void onKeyPressed(const Keyboard::Key& key);
				void onKeyReleased(const Keyboard::Key& key);

			private:
				CameraController& _cntrl;
		};

		class MListener : public Mouse::Listener
		{
			public:
				MListener(CameraController& cntrl);
				void onPerformed(const Mouse::ClickEvent& click) override;

			private:
				CameraController& _cntrl;
		};

		CameraController(const CameraPtr& camera);
		~CameraController() {}

		KBListener* getKBListener();
		MListener* getMListener();

	private:
		CameraPtr _camera;
		KBListener* _kb;
		MListener* _m;

		bool _flyEnabled;
		float _velocity;
		float _sensivity;

		void _onKey(const Keyboard::Key& key);
		void _onMouseMove(const int& x, const int& y);
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
