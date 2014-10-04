#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>
#include <stdexcept>


#define __DEBUG__


static const char ERR_BAD_ALLOC[] = "Not enough memory!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size must be grater than 1!";
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= index <= <universe size> - 1)!";

static const int MAX_HEALTH = 5;
static const int ZERO_HEALTH = 0;


enum LifeformState
{
	ALIVE, // 0
	HURT, // 1
	DEAD, // 2

	RECENTLY_BORN, // 3
	RECENTLY_DEAD // 4
};


class Lifeform
{
	public:
		Lifeform(const LifeformState state=DEAD);
		~Lifeform();

		Lifeform(const Lifeform& form);

		Lifeform& operator=(const Lifeform& form);
		friend std::ostream& operator<<(std::ostream& output, const Lifeform& form);

		friend int operator+(int x, Lifeform& form);
		friend int operator+(const Lifeform& form1, const Lifeform& form2);
		int get_neighbours_num() const { return _neighbours_num; }
		void set_neighbours_num(const int n) { _neighbours_num = n; }
		bool apply_state();

		bool is_alive() const;
		
		bool attack(const int points);
		bool heal(const int points);
		
		bool born();
		bool kill();

	private:
		int _health;
		int _neighbours_num;
		LifeformState _state;
};

std::ostream& operator<<(std::ostream& output, const Lifeform& form);
int operator+(int x, Lifeform& form);
int operator+(const Lifeform& form1, const Lifeform& form2);


class Universe
{
	public:
		Universe(const int length=10);
		~Universe();

		Universe(const Universe& u);

		bool init(const int x, const int y, const LifeformState state);
		bool init_from_file();

		bool is_freezed() const;
		int count_neighbours_number(const int x, const int y) const;

		void do_step();
		void draw();

	private:
		Lifeform **_data;
		int _width;
		int _step;
};


#endif