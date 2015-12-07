#include <iostream>
#include <sstream>
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
	for (const LifeObject *obj : this->_map.get_objects())
		render_object(*obj);
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
	int width = this->_map.get_width();
	int height = this->_map.get_height();

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

	for (const LifeObject *obj : this->_map.get_objects())
		render_object(*obj);
}


void ConsoleView::render_object(const LifeObject &obj) const
{
	const Point &obj_pos = obj.get_position();

	char chr;
	Palette clr;

	if (obj.is_alive())
	{
		switch (obj.get_type())
		{
			case LifeObject::Type::plant:
				chr = plant_view;
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
	}
	else
	{
		chr = dead_view;
		clr = Palette::dead;
	}

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
		clear_object(*obj);
}


void ConsoleView::clear_object(const LifeObject &obj) const
{
	const Point &obj_pos = obj.get_position();
	paint(obj_pos['x'], obj_pos['y'], empty_view, Palette::field);
}


TextView::TextView(const PopulationMap &map)
	: AbstractView(map)
{
}


TextView::~TextView()
{
}


void TextView::initialize_map_view() const
{
	con_clearScr();
}


void TextView::render_object(const LifeObject &obj) const
{
	std::string type;
	switch (obj.get_type())
	{
		case LifeObject::Type::plant:
			type = "Plnt";
			break;

		case LifeObject::Type::herbivorous:
			type = "Herb";
			break;

		case LifeObject::Type::predator:
			type = "Pred";
			break;

		default:
		case LifeObject::Type::none:
			type = "None";
			break;
	}

	std::stringstream ss;
	ss << type << ": "
	   << obj.get_health() << " hp "
	   << obj.get_mass() << "m "
	   << obj.get_position();
	con_outTxt("%s\n", ss.str().c_str());
}


void TextView::clear_map() const
{
	con_clearScr();
}
