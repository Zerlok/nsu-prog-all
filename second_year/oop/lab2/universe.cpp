#include "game.h"


Universe::Universe(const int length, const LifeformAction criteria[9])
{
	if (length < 1)
	{
		throw std::invalid_argument(ERR_BAD_UNIVERSE_SIZE);
	}

	_width = length;
	_step = 0;
	for (int i = 0; i < 9; i++) _life_criteria[i] = criteria[i];

	try
	{
		_data = new Lifeform*[_width];
		for (int x = 0; x < _width; x++) _data[x] = new Lifeform[_width];
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


Universe::Universe(const std::string filename)
{
	int x, y;
	std::ifstream file;
	std::string line;
	char cell;

	file.open(filename.c_str());

	getline(file, line); // #LifeGame ...
	getline(file, line); // #N Den Universe!
	file >> line; // #R
	
	// TODO: Read lifeforms criteria.
	for (x = 0; x < 9; x++)
	{
		_life_criteria[x] = STD_CRITERIA[x];
		file >> cell; // <criteria nums>
	}

	file >> line >> _step >> line; // #S <step> #U

	_width = 0;

	while (getline(file, line)) // <universe cells>
	{
		if (_width == 0)
		{
			_width = line.size();
			_data = new Lifeform*[_width];
		}

		for (x = 0; x < _width; x++)
		{
			_data[x] = new Lifeform[_width];

			for (y = 0; y < _width; y++)
			{
				file >> cell; // '.' or 'x'

				if (cell == 'x') init(x, y);
			}
		}
	}
}


void Universe::save_to_file(std::string filename)
{
	int x, y;
	std::ofstream file;
	file.open(filename.c_str());

	file << "#LifeGame (developer: Zerlok)\n";
	file << "#N Den Universe!\n";
	file << "#R ";

	for (x = 0; x < 9; x++)
	{
		file << _life_criteria[x];
	}

	file << "\n";
	file << "#S " << _step << "\n";
	file << "#U\n";

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			if (_data[x][y].is_alive())
			{
				file << ALIVE_FORM_FILE;
			}
			else
			{
				file << DEAD_FORM_FILE;
			}
		}

		file << "\n";
	}

	file.close();
}


bool Universe::init(const int x, const int y, const LifeformState state)
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
	{
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	}
	
	_data[x][y].set_state(state);

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
			if (_data[x][y].is_alive())
			{
				std::cout << ALIVE_FORM;
			}
			else
			{
				std::cout << DEAD_FORM;
			}
			std::cout << " ";
		}
		std::cout << "|" << std::endl;
	}

	std::cout << "+";
	for (x = 0; x < (2 * _width)+1; x++) std::cout << "-";
	std::cout << "+" << std::endl;
}
