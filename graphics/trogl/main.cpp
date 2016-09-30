#include <iostream>
#include <logger.hpp>

using namespace std;

int main(int argc, char *argv[])
{
	Logger::init();
	Logger::info() << "Main is running!" << logEnd;
	return 0;
}
