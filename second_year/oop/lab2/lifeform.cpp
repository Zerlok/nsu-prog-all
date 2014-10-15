#include "game.h"


Lifeform::Lifeform(const LifeformState state)
{
	_state = state;
	_neighbours_num = 0;
}


Lifeform::~Lifeform() {}


int operator+(int x, Lifeform& form)
{
	return x + form.is_alive();
}


int operator+(const Lifeform& form1, const Lifeform& form2)
{
	return form1.is_alive() + form2.is_alive();
}


void Lifeform::apply_state(const bool born_criteria[9], const bool survival_criteria[9])
{
	if (_state == DEAD)
	{
		if (born_criteria[_neighbours_num]) born();
	}
	else
	{
		if (!survival_criteria[_neighbours_num]) kill();
	}
}


void Lifeform::set_neighbours_num(const int n)
{
	_neighbours_num = n;
}


void Lifeform::set_state(const LifeformState state)
{
	_state = state;
}


bool Lifeform::is_alive() const
{
	switch (_state)
	{
		case ALIVE: return true;
	}

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