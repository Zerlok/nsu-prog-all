#ifndef __LAMP_HPP__
#define __LAMP_HPP__


#include "object.hpp"


class Lamp : public Object
{
	public:
		Lamp();
		Lamp(const Lamp& lamp);
		Lamp(Lamp&& lamp);
		~Lamp();

		Lamp& operator=(const Lamp& lamp);
		Lamp& operator=(Lamp&& lamp);
};


#endif // __LAMP_HPP__
