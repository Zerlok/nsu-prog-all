#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>


#define __DEBUG__
#define __DEBUG__MAIN__
// #define __DEBUG__UNIVERSE__
// #define __DEBUG__LIFEFORM__


static const char ERR_BAD_ALLOC[] = "Not enough memory!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size must be grater than 1!";
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";


static const int STD_UNIVERSE_SIZE = 36;

static const char ALIVE_FORM_FILE = '#';
static const char DEAD_FORM_FILE = '.';

#ifdef __DEBUG__LIFEFORM__
static const char ALIVE_FORM = '@';
static const char DEAD_FORM = '.';
#else
static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';
#endif


enum LifeformState
{
	ALIVE, // Alive form.
	DEAD // Dead form.
};

static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};


class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		friend int operator+(int x, Lifeform& form);
		friend int operator+(const Lifeform& form1, const Lifeform& form2);

		void apply_state(const bool born_criteria[9], const bool survival_criteria[9]);
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
		Universe(const int length = STD_UNIVERSE_SIZE,
				const bool born_criteria[9] = STD_BORN_CRITERIA,
				const bool survival_criteria[9] = STD_SURVIVAL_CRITERIA
		);

		~Universe();

		Universe(const std::string filename);
		void save_to_file(std::string filename);

		bool init(const int x, const int y, const LifeformState state = ALIVE);

		int count_neighbours(const int x, const int y) const;
		unsigned long long int count_alive_forms() const;

		void do_step();
		void draw();

	private:
		Lifeform **_data;
		int _width;
		int _step;
		bool _born_criteria[9];
		bool _survival_criteria[9];
};


// __LIFEGAME_H__
#endif
