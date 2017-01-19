#ifndef __PROJECT_SHADOWS_HPP__
#define __PROJECT_SHADOWS_HPP__


#include <string>
#include <list>
#include "task.hpp"


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
};


class ShadowsTesting : public Tester
{
	public:
		ShadowsTesting();
		~ShadowsTesting() {}
};


#endif // __PROJECT_SHADOWS_HPP__
