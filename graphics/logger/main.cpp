#include <iostream>


#include "logger.hpp"



logger_t log = logger_i(std::cout, logger_l::DEBUG, logger_d::FULL);



int function(int a)
{
	logInfo << "Input argument: " << a << logEndl;
	return a+100;
}


int main(int argc, char *argv[])
{
	logDebug << "hello, debug!" << logEndl;
	logInfo << "hello, info!" << logEndl;

	Logger::init();

	logWarning << "hello, warning!" << logEndl;

	if (function(10) < 200)
		logError << "hello, error!" << logEndl;

	logWarning << "This is it!" << logEndl;

	return 0;
}
