#include "object.h"


int main(int argc, char **argv)
{
	Object o("MyObj"), o1("ololo"), o2;

	std::cout << o << std::endl
			<< o1 << std::endl
			<< o2 << std::endl;

	return 0;
}