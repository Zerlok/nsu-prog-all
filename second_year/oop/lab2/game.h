#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>


// #define __DEBUG__


static const char ERR_BAD_ALLOC[] = "Not enough memory!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size must be grater than 1!";
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";


static const int STD_SIZE = 36;

static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';

static const char ALIVE_FORM_FILE = 'x';
static const char DEAD_FORM_FILE = '.';


enum LifeformState
{
	ALIVE, // Alive form.
	DEAD // Dead form.
};


enum LifeformAction
{
	BORN, // Make the Lifeform alive.
	KEEP, // Keep the Lifeform state.
	KILL  // Kill the Lifeform.
};


/* Lifeform neighbours sum criteria (if sum equals 0 - the action is kill etc.): */
static const LifeformAction STD_CRITERIA[9] = {
	KILL, // 0
	KILL, // 1
	KEEP, // 2
	BORN, // 3
	KILL, // 4
	KILL, // 5
	KILL, // 6
	KILL, // 7
	KILL  // 8
};


class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		friend int operator+(int x, Lifeform& form);
		friend int operator+(const Lifeform& form1, const Lifeform& form2);

		void apply_state(const LifeformAction criteria[]);
		void set_neighbours_num(const int n);
		void set_state(const LifeformState state);

		bool is_alive() const;
		
		bool born();
		bool kill();

	private:
		LifeformState _state;
		int _neighbours_num;
};

int operator+(int x, Lifeform& form);
int operator+(const Lifeform& form1, const Lifeform& form2);


class Universe
{
	public:
		Universe(const int length = STD_SIZE,
				const LifeformAction criteria[9] = STD_CRITERIA
		);

		~Universe();

		Universe(const std::string filename);
		void save_to_file(std::string filename);

		bool init(const int x, const int y, const LifeformState state = ALIVE);

		int count_neighbours_number(const int x, const int y) const;

		void do_step();
		void draw();

	private:
		Lifeform **_data;
		int _width;
		int _step;
		LifeformAction _life_criteria[9];
};


// __LIFEGAME_H__
#endif
