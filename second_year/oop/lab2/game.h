#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <unistd.h>


#define __DEBUG__


static const char ERR_BAD_ALLOC[] = "Not enough memory!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size must be grater than 1!";
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";


static const int STD_SIZE = 36;

#ifdef __DEBUG__
static const char ALIVE_FORM = 'x';
static const char DEAD_FORM = '.';
#else
static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';
#endif


enum LifeformAction
{
	BORN, // Make the Lifeform alive.
	KEEP, // Keep the Lifeform state.
	KILL  // Kill the Lifeform.
};

/* Lifeform neighbours sum criteria (if sum equals 0 - the action is kill): */
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


enum LifeformState
{
	ALIVE,
	DEAD
};


class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		Lifeform(const Lifeform& form);

		Lifeform& operator=(const Lifeform& form);
		friend std::ostream& operator<<(std::ostream& output, const Lifeform& form);

		friend int operator+(int x, Lifeform& form);
		friend int operator+(const Lifeform& form1, const Lifeform& form2);

		void set_neighbours_num(const int n) { _neighbours_num = n; }
		bool apply_state(const LifeformAction criteria[]);

		bool is_alive() const;
		
		bool born();
		bool kill();

	private:
		int _neighbours_num;
		LifeformState _state;
};

std::ostream& operator<<(std::ostream& output, const Lifeform& form);
int operator+(int x, Lifeform& form);
int operator+(const Lifeform& form1, const Lifeform& form2);


class Universe
{
	public:
		Universe(const int length = 10,
				const LifeformAction criteria[9] = STD_CRITERIA
		);
		~Universe();

		Universe(const Universe& u);

		bool init(const int x, const int y, const LifeformState state);

		int count_neighbours_number(const int x, const int y) const;

		void do_step();
		void draw();
		void save_to_file(std::string filename);

	private:
		Lifeform **_data;
		int _width;
		int _step;
		LifeformAction _life_criteria[9];
};


// __LIFEGAME_H__
#endif
