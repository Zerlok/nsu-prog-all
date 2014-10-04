#include "game.h"


Universe::Universe(const int length)
{
	if (length < 1)
	{
		throw std::invalid_argument(ERR_BAD_UNIVERSE_SIZE);
	}

	_width = length;
	_step = 0;

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
	_step = u._step;

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
}


bool Universe::init(const int x, const int y, const LifeformState state)
{
	Lifeform point(state);

	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}
	
	_data[x][y] = point;

	return true;
}


bool Universe::init_from_file()
{
	return false;
}


bool Universe::is_freezed() const
{
	return false;
}


int Universe::count_neighbours_number(const int x, const int y) const
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}

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


void Universe::do_step()
{
	int x, y, sum;

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			_data[x][y].set_neighbours_num(count_neighbours_number(x,y));
			// std::cout << "[" << x << ", " << y << "]";
		}
	}

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			_data[x][y].apply_state();
		}
	}

	_step++;
}


void Universe::draw()
{
	int x;
	
	std::cout << "Universe step: [" << _step << "]" << std::endl;

	std::cout << "+";
	for (x = 0; x < (2 * _width)+1; x++) std::cout << "-";
	std::cout << "+ y" << std::endl;

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
	std::cout << "+" << std::endl << "x" << std::endl;
}