#include "game.h"

// private:
// 	int _health;
// 	LifeformState _state;


Lifeform::Lifeform(const LifeformState state)
{
	_state = state;
	_neighbours_num = 0;

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

		default:
		{
			_health = ZERO_HEALTH;
			_state = DEAD;
			break;
		}
	}
}


Lifeform::~Lifeform() {}


Lifeform::Lifeform(const Lifeform& form)
{
	_health = form._health;
	_state = form._state;
	_neighbours_num = form._neighbours_num;
}


Lifeform& Lifeform::operator=(const Lifeform& form)
{
	_health = form._health;
	_state = form._state;
	_neighbours_num = form._neighbours_num;

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
		case ALIVE: return true;
		default: return false;
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


bool Lifeform::apply_state()
{
	if (_neighbours_num >= 3 && _neighbours_num <= 5)
	{
		born();
		return true;
	}

	kill();
	return true;
}


bool Lifeform::born()
{
	if (_state == ALIVE) return false;
	
	_health = MAX_HEALTH;
	_state = ALIVE;

	return true;

	// std::cout << "born - (was " << _state << ")";

	// switch (_state)
	// {
	// 	// case ALIVE: return false;
	// 	case RECENTLY_DEAD:
	// 	{
	// 		return kill();
	// 	}
		
	// 	case DEAD:
	// 	{
	// 		_state = RECENTLY_BORN;
	// 		return true;
	// 	}
	// }
}


bool Lifeform::kill()
{
	if (_state == DEAD) return false;
	
	_health = ZERO_HEALTH;
	_state = DEAD;
	
	return true;
}

	// switch (_state)
	// {
	// 	case RECENTLY_BORN:
	// 	{
	// 		return born();
	// 	}
		
	// 	case ALIVE:
	// 	{
	// 		_state = RECENTLY_DEAD;
	// 		return true;
	// 	}
	// }
