#include "game.h"


Universe::Universe(const int length, const LifeformAction criteria[9])
{
	if (length < 1)
	{
		throw std::invalid_argument(ERR_BAD_UNIVERSE_SIZE);
	}

	_width = length;
	_step = 0;

	try
	{
		for (int i = 0; i < 9; i++) _life_criteria[i] = criteria[i];
		
		_data = new Lifeform*[_width];

		Lifeform point(DEAD);
		for (int x = 0; x < _width; x++)
		{
			_data[x] = new Lifeform[_width];

			for (int y = 0; y < _width; y++) _data[x][y] = point;
		}
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
	_step = u._step;

	try
	{
		for (int i = 0; i < 9; i++)
		{
			_life_criteria[i] = u._life_criteria[i];
		}

		_data = new Lifeform*[_width];

		for (int x = 0; x < _width; x++)
		{
			_data[x] = new Lifeform[_width];
			for (int y = 0; y < _width; y++) _data[x][y] = u._data[x][y];
		}
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}
}


bool Universe::init(const int x, const int y, const LifeformState state)
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}
	
	Lifeform point(state);
	_data[x][y] = point;

	return true;
}


int Universe::count_neighbours_number(const int x, const int y) const
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}

	/*
	There are the dot's neighbours (the dot location is x, y):
		+-------+
		| 8 1 2 |
		| 7 . 3 |
		| 6 5 4 |
	   	+-------+
	*/

	return (
			_data[(x-1 + _width) % _width][y] +	// 1
			_data[(x+1 + _width) % _width][y] + // 5
			_data[x][(y+1 + _width) % _width] + // 3
			_data[x][(y-1 + _width) % _width] + // 7
			_data[(x-1 + _width) % _width][(y+1 + _width) % _width] + // 2
			_data[(x+1 + _width) % _width][(y+1 + _width) % _width] + // 4
			_data[(x+1 + _width) % _width][(y-1 + _width) % _width] + // 6
			_data[(x-1 + _width) % _width][(y-1 + _width) % _width]   // 8
	);
}


// TODO: Rewrite with only one cycle.
void Universe::do_step()
{
	int x, y;

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			_data[x][y].set_neighbours_num(count_neighbours_number(x, y));
		}
	}

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			_data[x][y].apply_state(_life_criteria);
		}
	}

	_step++;
}


void Universe::draw()
{
	int x;
	
	std::cout << "Universe step: " << _step << std::endl;

	std::cout << "+";
	for (x = 0; x < (2 * _width)+1; x++) std::cout << "-";
	std::cout << "+" << std::endl;

	for (x = 0; x < _width; x++)
	{
		std::cout << "| ";
		for (int y = 0; y < _width; y++)
		{
			std::cout << _data[x][y] << " ";
		}
		std::cout << "|" << std::endl;
	}

	std::cout << "+";
	for (x = 0; x < (2 * _width)+1; x++) std::cout << "-";
	std::cout << "+" << std::endl;
}
