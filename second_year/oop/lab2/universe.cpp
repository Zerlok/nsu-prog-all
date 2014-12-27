#include "main.h"
#include "lifeform.h"
#include "universe.h"


Universe::Universe(
		const int length,
		const bool born_criteria[9],
		const bool survival_criteria[9])
{
	if (length < 1)
		throw std::invalid_argument(ERR_BAD_UNIVERSE_SIZE);

	_width = length;
	_step = 0;

	for (int i = 0; i < 9; i++)
	{
		_born_criteria[i] = born_criteria[i];
		_survival_criteria[i] = survival_criteria[i];
	}

	_data = new Lifeform*[_width];
	for (int i = 0; i < _width; i++)
		_data[i] = new Lifeform[_width];
}


Universe::~Universe()
{
	for (int i = 0; i < _width; i++)
		delete[] _data[i];

	delete[] _data;
}


Universe::Universe(const std::string& filename)
{
	int x, y;
	std::ifstream file(filename.c_str());
	std::string line;
	char cell;

	#ifdef __DEBUG__
	std::cout << "Opening " << filename << "..." << std::endl;
	#endif

	if (!file.is_open())
		throw std::invalid_argument(ERR_INVALID_INPUT_FILE);
	
	for (x = 0; x < 9; x++)
	{
		_born_criteria[x] = false;
		_survival_criteria[x] = false;
	}

	std::getline(file, line); // #L
	std::getline(file, line); // #N Den Universe!
	file >> line; // #R
	
	file >> cell;
	file >> cell;
	while (cell != '/')
	{
		_born_criteria[(cell - '0')] = true;
		file >> cell;
	}

	file >> cell;
	file >> cell;
	while (cell != '#')
	{
		_survival_criteria[(cell - '0')] = true;
		file >> cell;
	}

	file >> line;
	file >>_step >> line; // #S <step> (#U or #M)
	
	file >> _width;

	_data = new Lifeform*[_width];
	for (x = 0; x < _width; x++)
	{
		_data[x] = new Lifeform[_width];
		for (y = 0; y < _width; y++) init(x, y, DEAD);
	}

	if (line == "#U")
	{
		while (file >> x >> y) // TODO: while the end of file (EOF).
		{
			init(x, y, ALIVE);
		}
	}
	else if (line == "#M")
	{
		for (x = 0; x < _width; x++)
		{
			for (y = 0; y < _width; y++)
			{
				file >> cell;

				if (cell == ALIVE_FORM_FILE)
				{
					init(x, y, ALIVE);
				}
				else if (cell != DEAD_FORM_FILE)
				{
					#ifdef __DEBUG__
					std::cout << "Unknown cell was readen: " << cell;
					std::cout << "(" << ALIVE_FORM_FILE << ", " << DEAD_FORM_FILE << ")" << std::endl;
					#endif
				}
			}
		}
	}
	else
	{
		std::cout << "# Life file is invalid!" << std::endl;
		std::cout << "# " << line << std::endl;
	}
}


void Universe::write_to_file(const std::string& filename) const
{
	int x, y;
	bool map_format;
	std::ofstream file;
	int width_digits_num = std::to_string(_width).size();
	file.open(filename.c_str());

	file << "#L\n";
	file << "#N " << filename << "\n";
	file << "#R B";

	for (x = 0; x < 9; x++)
	{
		if (_born_criteria[x])
			file << x;
	}

	file << "/S";
	for (x = 0; x < 9; x++)
	{
		if (_survival_criteria[x])
			file << x;
	}

	file << "\n";
	file << "#S " << _step << "\n";

	if (count_alive_forms() >
		(size_t)(_width / (2 * width_digits_num) * _width))
	{
		/* Saving all universe map. */
		file << "#M " << _width << "\n";
		map_format = true;
	}
	else
	{
		/* Saving alive forms coordinates. */
		file << "#U " << _width << "\n";
		map_format = false;
	}

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			if (_data[x][y].is_alive())
			{
				if (map_format)
				{
					file << ALIVE_FORM_FILE;
				}
				else
				{
					file << x << " " << y << "\n";
				}
			}
			else
			{
				if (map_format)
					file << DEAD_FORM_FILE;
			}
		}

		if (map_format)
			file << "\n";
	}

	file.close();
}


bool Universe::init(
		const int x,
		const int y,
		const LifeformState state)
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);
	
	_data[x][y] = state;

	return true;
}


size_t Universe::count_alive_forms() const
{
	size_t total = 0;
	int x, y;

	for (x = 0; x < _width; x++)
		for (y = 0; y < _width; y++)
			if (_data[x][y].is_alive())
				total++;

	return total;
}


int Universe::count_neighbours(const int x, const int y) const
{
	if (x < 0 || y < 0 || x > _width-1 || y > _width-1)
		throw std::invalid_argument(ERR_INDEX_OUT_RANGE);

	/*
	 * There are the dot's neighbours (the dot location is x, y):
	 *  +-------+
	 *  | 8 1 2 |
	 *  | 7 . 3 |
	 *  | 6 5 4 |
	 *  +-------+
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
	int x;
	int y;
	int num;

	for (x = 0; x < _width; x++)
	{
		for (y = 0; y < _width; y++)
		{
			num = count_neighbours(x, y);
			_data[x][y].set_neighbours_num(num);

			#ifdef __DEBUG__UNIVERSE__
			std::cout << "(" << x << ", " << y << ")" << " : " << num << std::endl;
			#endif
		}
	}

	for (x = 0; x < _width; x++)
		for (y = 0; y < _width; y++)
			_data[x][y].apply_state_by_criteria(
					_born_criteria,
					_survival_criteria);

	_step++;
}


void Universe::draw() const
{
	int x;
	
	std::cout << "Universe step: " << _step;

	std::cout << " Criteria: B";
	for (int i = 0; i < 9; i++)
	{
		if (_born_criteria[i]) std::cout << i;
	}
	std::cout << "/S";
	for (int i = 0; i < 9; i++)
	{
		if (_survival_criteria[i]) std::cout << i;
	}
	#ifdef __DEBUG__
	std::cout << "(" << count_alive_forms() << ")";
	#endif
	std::cout << std::endl;

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
	for (x = 0; x < (2 * _width) + 1; x++) std::cout << "-";
	std::cout << "+" << std::endl;
}
