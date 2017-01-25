#include <iostream>


#include "logger.hpp"
#include "myclass.h"


int function(int a)
{
	logInfo << "Input argument: " << a << logEndl;
	return a+100;
}


loggerType log = loggerInit(std::cout,
							Logger::Level::DEBUG,
							Logger::Description::LEVEL);


int main(int argc, char *argv[])
{
	logDebug << "hello, debug!" << logEndl;
	logInfo << "hello, info!" << logEndl;

	MyClass obj;

	logWarning << "hello, warning!" << logEndl;

	if (function(10) < 200)
		logError << "hello, error!" << logEndl;

	logWarning << "This is it!" << logEndl;

	return 0;
}
