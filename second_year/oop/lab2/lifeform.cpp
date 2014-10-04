#include "game.h"

// private:
// 	int _health;
// 	LifeformState _state;


Lifeform::Lifeform(const LifeformState state)
{
	_state = state;

	switch (state)
	{
		case ALIVE:
		{
			_health = MAX_HEALTH;
			break;
		}

		case HURT:
		{
			_health = MAX_HEALTH;
			break;
		}

		case DEAD:
		{
			_health = ZERO_HEALTH;
			break;
		}
	}
}


Lifeform::~Lifeform() {}


Lifeform::Lifeform(const Lifeform& form)
{
	_health = form._health;
	_state = form._state;
}


Lifeform& Lifeform::operator=(const Lifeform& form)
{
	_health = form._health;
	_state = form._state;

	return *this;
}


std::ostream& operator<<(std::ostream& output, const Lifeform& form)
{
	output << form.is_alive() ? "1" : "0";
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
		case DEAD: return false;
		default: return true;
	}
}


bool Lifeform::attack(const int points)
{
	if (points < 0) throw std::invalid_argument(ERR_NEGATIVE_VALUE);

	if (_health <= 0) return false;

	_health -= points;
	_state = HURT;

	if (_health <= 0) kill();

	return true;
}


bool Lifeform::heal(const int points)
{
	if (points < 0) throw std::invalid_argument(ERR_NEGATIVE_VALUE);

	if (_state == DEAD) return false;

	_health += points;
	_state = ALIVE;

	if (_health > MAX_HEALTH) _health = MAX_HEALTH;

	return true;
}


bool Lifeform::born()
{
	if (_state != DEAD) return false;

	_health = MAX_HEALTH;
	_state = ALIVE;

	return true;
}


bool Lifeform::kill()
{
	if (_state == DEAD) return false;

	_health = ZERO_HEALTH;
	_state = DEAD;

	return true;
}
