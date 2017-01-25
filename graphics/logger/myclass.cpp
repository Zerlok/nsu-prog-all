#include "myclass.h"


#include "logger.hpp"


loggerType log = logerForModule(Logger::Level::INFO, Logger::Description::FULL);


MyClass::MyClass()
{
	logModule << "Construct" << logEndl;
}


MyClass::~MyClass()
{
	logModule << "Destroy" << logEndl;
}
