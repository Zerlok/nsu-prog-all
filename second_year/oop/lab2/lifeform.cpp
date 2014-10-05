#include "game.h"


Lifeform::Lifeform(const LifeformState state)
{
	_state = state;
	_neighbours_num = 0;
}


Lifeform::~Lifeform() {}


Lifeform::Lifeform(const Lifeform& form)
{
	_state = form._state;
	_neighbours_num = form._neighbours_num;
}


Lifeform& Lifeform::operator=(const Lifeform& form)
{
	_state = form._state;
	_neighbours_num = form._neighbours_num;

	return *this;
}


std::ostream& operator<<(std::ostream& output, const Lifeform& form)
{
	if (form.is_alive())
	{
		output << ALIVE_FORM;
	}
	else
	{
		output << DEAD_FORM;
	}
	
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


bool Lifeform::apply_state(const LifeformAction criteria[])
{
	switch (criteria[_neighbours_num])
	{
		case BORN: return born();
		case KILL: return kill();
		case KEEP: return true;
	}

	return true;
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
