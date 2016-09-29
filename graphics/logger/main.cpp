#include <iostream>


#include "logger.hpp"


int function(int a)
{
	logInfo << "Input argument: " << a << logEnd;
	return a+100;
}


int main(int argc, char *argv[])
{
	Logger::init(std::cout, Logger::Level::INFO);

	Logger::debug() << "hello, debug!" << Logger::end;
	Logger::info() << "hello, info!" << Logger::end;

	Logger::init();

	Logger::warning() << "hello, warning!" << Logger::end;

	if (function(10) < 200)
		Logger::error() << "hello, error!" << Logger::end;

	logWarningFull << "This is it!" << logEnd;

	return 0;
}
