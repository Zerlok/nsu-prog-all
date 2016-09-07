#include <iostream>
#include <sstream>
#include <cstdint>
#include "console.h"

#include "populationmapview.h"


AbstractView::AbstractView(const PopulationMap &map)
	: _map(map)
{
}


AbstractView::~AbstractView()
{
}


void AbstractView::render_map() const
{
	for (const LifeObject *obj : _map.get_objects())
		render_object(obj);
}


ConsoleView::ConsoleView(const PopulationMap &map)
	: AbstractView(map)
{
	con_initPair(short(Palette::text), CON_COLOR_WHITE, CON_COLOR_BLACK);
	con_initPair(short(Palette::field), CON_COLOR_GREEN, CON_COLOR_GREEN);
	con_initPair(short(Palette::dead), CON_COLOR_WHITE, CON_COLOR_GREEN);
	con_initPair(short(Palette::plant), CON_COLOR_WHITE, CON_COLOR_GREEN);
	con_initPair(short(Palette::herbivorous), CON_COLOR_BLACK, CON_COLOR_GREEN);
	con_initPair(short(Palette::predator), CON_COLOR_RED, CON_COLOR_GREEN);
}


ConsoleView::~ConsoleView()
{
	con_clearScr();
}


void ConsoleView::initialize_map_view() const
{
	int width = _map.get_width();
	int height = _map.get_height();

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			paint(x, y, empty_view, Palette::field);
}


void ConsoleView::render_map() const
{
	int header_x_pos = _map.get_width() + 1;
	con_setColor(short(Palette::text));
	con_gotoXY(header_x_pos, 1);
	con_outTxt("Plants: %d", _map.get_plants_num());
	con_gotoXY(header_x_pos, 2);
	con_outTxt("Herbivorous: %d", _map.get_herbivorous_num());
	con_gotoXY(header_x_pos, 3);
	con_outTxt("Predators: %d", _map.get_predators_num());

	for (const LifeObject *obj : _map.get_objects())
		render_object(obj);
}


void ConsoleView::render_object(const LifeObject *obj) const
{
	const Point &obj_pos = obj->get_position();

	char chr;
	Palette clr;

	switch (obj->get_type())
	{
		case LifeObject::Type::plant:
			if (!(obj->is_alive()))
				return;

			chr = get_plant_view(obj);
			clr = Palette::plant;
			break;

		case LifeObject::Type::herbivorous:
			chr = herbivorous_view;
			clr = Palette::herbivorous;
			break;

		case LifeObject::Type::predator:
			chr = predator_view;
			clr = Palette::predator;
			break;

		default:
		case LifeObject::Type::none:
			chr = empty_view;
			clr = Palette::field;
			break;
	}

	if (!(obj->is_alive()))
		chr = dead_view;

	paint(obj_pos['x'], obj_pos['y'], chr, clr);
}


void ConsoleView::paint(int x, int y, char chr, const Palette &clr) const
{
	con_gotoXY(x, y);
	con_setColor(short(clr));
	con_outTxt("%c", chr);
}


void ConsoleView::clear_map() const
{
	int header_x_pos = _map.get_width() + 1;
	con_setColor(short(Palette::text));

	for (int i = 1; i < 4; ++i)
	{
		con_gotoXY(header_x_pos, i);
		con_outTxt("                  ");
	}

	for (const LifeObject *obj : _map.get_objects())
		clear_object(obj);
}


char ConsoleView::get_plant_view(const LifeObject *plant) const
{
	uintptr_t id = reinterpret_cast<uintptr_t>(plant);

	switch (id % 5)
	{
		case 0:
			return ';';
		case 1:
			return ',';
		case 2:
			return '\'';
		case 3:
			return '"';

		default:
		case 4:
			return '`';
	}
}


void ConsoleView::clear_object(const LifeObject *obj) const
{
	const Point &obj_pos = obj->get_position();
	paint(obj_pos['x'], obj_pos['y'], empty_view, Palette::field);
}


TextView::TextView(const PopulationMap &map, std::ostream &out)
	: AbstractView(map),
	  _out(out)
{
}


TextView::~TextView()
{
}


void TextView::initialize_map_view() const
{
	_out << _map.get_width() << Config::file_data_separator << _map.get_height() << std::endl;
}


void TextView::render_object(const LifeObject *obj) const
{
	if (!(obj->is_eatable()))
		return;

	_out << obj->get_type()
	   << Config::file_data_separator << obj->get_health()
	   << Config::file_data_separator << obj->get_damage()
	   << Config::file_data_separator << obj->get_mass()
	   << Config::file_data_separator << obj->get_position()
	   << std::endl;
}


void TextView::clear_map() const
{
}
