#ifndef __PROJECT_SHADOWS_HPP__
#define __PROJECT_SHADOWS_HPP__


#include <string>
#include <list>
#include "task.hpp"
#include "task07.hpp"


class Tester : public Task
{
	public:
		using List = std::list<Task*>;

		Tester(const std::string& name);
		virtual ~Tester();

		void add(Task* test);
		void run() override;

	private:
		List _tests;
};


class TestRTT : public Task
{
	public:
		TestRTT();
		~TestRTT() {}

	private:
		CameraController _cameraCntrl;
};


class ShadowsTesting : public Tester
{
	public:
		ShadowsTesting();
		~ShadowsTesting() {}
};


class AnimController : public Keyboard::KeyListener
{
	public:
		AnimController(Animation& anim);
		void onKeyPressed(const Keyboard::Key& key);
		void onKeyReleased(const Keyboard::Key& key);

	private:
		Animation& _anim;
};


#endif // __PROJECT_SHADOWS_HPP__
