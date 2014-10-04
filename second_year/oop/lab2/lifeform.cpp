#include "game.h"


Lifeform::Lifeform(const LifeformState state)
{
	_state = state;
	_neighbours_num = 0;

	for (int i = 0; i < 8; i++) _around[i] = NULL;
}


void Lifeform::set_around(const int x, const int y, Lifeform **_data, const int w)
{
	_around[0] = &(_data[(x-1 + w) % w][y]);
	_around[1] = &(_data[(x-1 + w) % w][(y+1 + w) % w]);
	_around[2] = &(_data[x][(y+1 + w) % w]);
	_around[3] = &(_data[(x+1 + w) % w][(y+1 + w) % w]);
	_around[4] = &(_data[(x+1 + w) % w][y]);
	_around[5] = &(_data[(x+1 + w) % w][(y-1 + w) % w]);
	_around[6] = &(_data[x][(y-1 + w) % w]);
	_around[7] = &(_data[(x-1 + w) % w][(y-1 + w) % w]);
}


Lifeform::~Lifeform() {}


Lifeform::Lifeform(const Lifeform& form)
{
	_state = form._state;
	_neighbours_num = form._neighbours_num;

	for (int i = 0; i < 8; i++)
	{
		_around[i] = form._around[i];
	}
}


Lifeform& Lifeform::operator=(const Lifeform& form)
{
	_state = form._state;
	_neighbours_num = form._neighbours_num;

	for (int i = 0; i < 8; i++)
	{
		_around[i] = form._around[i];
	}

	return *this;
}


std::ostream& operator<<(std::ostream& output, const Lifeform& form)
{
	output << form.is_alive() ? "O" : ".";
	return output;
}


int operator+(int x, Lifeform& form)
{
	return x + form.is_alive();
}


int operator+(const Lifeform& form1, const Lifeform& form2)
{
	return form1.is_alive() + form2.is_alive();
}


bool Lifeform::is_alive() const
{
	switch (_state)
	{
		case ALIVE: return true;
		default: return false;
	}
}


int Lifeform::count_neighbours()
{
	// #ifdef __DEBUG__
	// std::cout << "1: (" <<
	// 		(x-1 + _width) % _width << " " << y << "), 2: (" <<
	// 		(x-1 + _width) % _width << " " << (y+1 + _width) % _width << "), 3: (" <<
	// 		x << " " << (y+1 + _width) % _width << "), 4: (" <<
	// 		(x+1 + _width) % _width << " " << (y+1 + _width) % _width << "), 5: (" <<
	// 		(x+1 + _width) % _width << " " << y << "), 6: (" <<
	// 		(x+1 + _width) % _width << " " << (y-1 + _width) % _width << "), 7: (" <<
	// 		x << " " << (y-1 + _width) % _width << "), 8: (" <<
	// 		(x-1 + _width) % _width << " " << (y-1 + _width) % _width << ")" << std::endl;
	// #endif

	/*
	There are the dot's neighbours (the dot location is x, y):
		+-------+
		| 7 0 1 |
		| 6 . 2 |
		| 5 4 3 |
	   	+-------+
	*/

	int sum = 0;

	for (int i = 0; i < 8; i++) sum = sum + *(_around[i]);

	_neighbours_num = sum;

	return sum;
}


bool Lifeform::apply_state()
{
	if (_neighbours_num >= 3 && _neighbours_num <= 5)
	{
		born();
		return true;
	}

	kill();
	return false;
}


bool Lifeform::born()
{
	if (_state == ALIVE) return false;

	_state = ALIVE;

	return true;
}


bool Lifeform::kill()
{
	if (_state == DEAD) return false;

	_state = DEAD;
	
	return true;
}