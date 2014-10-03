#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream>


#define __DEBUG__


class Cell
{
	public:
		Cell(const int px_size);
		~Cell();

		Cell(const Cell& cell);

		virtual void draw();

	private:
		int _pixels;
		
		int _red;
		int _green;
		int _blue;

		int _margin;
};


class Lifeform : public Cell
{
	public:
		Lifeform();
		~Lifeform();

		Lifeform(const Lifeform& form);

		bool is_alive();
		
		bool attack(const int point);
		bool heal(const int point);
		
		bool born(const int point);
		bool kill();

		virtual void draw();

	private:
		int _health;
		bool _is_infected;
		int _state;
};


class Universe : public Cell
{
	public:
		Universe(const int length);
		~Universe();

		Universe(const Universe& u);

		bool init();
		bool init_from_file();

		bool is_freezed() const;

		virtual void draw();

	private:
		Lifeform **_data;
		bool _has_alive_object;
		int _state;
};


#endif