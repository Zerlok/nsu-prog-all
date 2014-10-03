#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>
#include <stdexcept>


#define __DEBUG__


static const char ERR_BAD_ALLOC[] = "Not enough memory!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size must be grater than 1!";
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";

static const int MAX_HEALTH = 5;
static const int ZERO_HEALTH = 0;


enum LifeformState
{
	ALIVE,
	HURT,
	DEAD
};


class Lifeform
{
	public:
		Lifeform(const LifeformState state=DEAD);
		~Lifeform();

		Lifeform(const Lifeform& form);

		Lifeform& operator=(const Lifeform& form);
		friend std::ostream& operator<<(std::ostream& output, const Lifeform& form);

		bool is_alive() const;
		
		bool attack(const int points);
		bool heal(const int points);
		
		bool born();
		bool kill();

	private:
		int _health;
		LifeformState _state;
};

std::ostream& operator<<(std::ostream& output, const Lifeform& form);


class Universe
{
	public:
		Universe(const int length=10);
		~Universe();

		Universe(const Universe& u);

		bool init(const int x, const int y, const LifeformState state);
		bool init_from_file();

		bool is_freezed() const;

		void draw();

	private:
		Lifeform **_data;
		int _width;
		bool _has_alive_object;
		int _state;
};


#endif