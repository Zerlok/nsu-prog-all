#include "game.h"


Universe::Universe(const int length)
{
	if (length < 1)
	{
		throw std::invalid_argument(ERR_BAD_UNIVERSE_SIZE);
	}

	_width = length;

	Lifeform point(DEAD);


	try
	{
		_data = new Lifeform*[length];
		for (int x = 0; x < _width; x++) _data[x] = new Lifeform[length];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}
}


Universe::~Universe()
{
	for (int i = 0; i < _width; i++)
	{
		delete[] _data[i];
	}

	delete _data;
}


Universe::Universe(const Universe& u)
{
	_width = u._width;

	try
	{
		_data = new Lifeform*[_width];
		for (int x = 0; x < _width; x++) _data[x] = new Lifeform[_width];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _width; y++)
		{
			_data[x][y] = u._data[x][y];
		}
	}

	_has_alive_object = u._has_alive_object;
}


bool Universe::init(const int x, const int y, const LifeformState state)
{
	Lifeform point(state);

	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}
	
	_data[x][y] = point;

	if (state != DEAD)
	{
		_has_alive_object = true;
	}

	return true;
}


bool Universe::init_from_file()
{
	return false;
}


bool Universe::is_freezed() const
{
	return !_has_alive_object;
}


void Universe::draw()
{
	int x;

	std::cout << "+";
	for (x = 0; x < (2 * _width)-1; x++) std::cout << "-";
	std::cout << "+" << std::endl;

	for (x = 0; x < _width; x++)
	{
		Lifeform *p_form = _data[x];

		std::cout << "|";
		for (int y = 0; y < _width; y++)
		{
			std::cout << p_form[y] << " ";
		}
		std::cout << "\b|" << std::endl;
	}

	std::cout << "+";
	for (x = 0; x < (2 * _width)-1; x++) std::cout << "-";
	std::cout << "+" << std::endl;
}
