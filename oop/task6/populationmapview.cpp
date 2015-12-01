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
	con_initPair(short(Palette::border_color), CON_COLOR_WHITE, CON_COLOR_BLACK);
	con_initPair(short(Palette::field_color), CON_COLOR_GREEN, CON_COLOR_GREEN);
	con_initPair(short(Palette::plant_color), CON_COLOR_BLACK, CON_COLOR_GREEN);
	con_initPair(short(Palette::herbivorous_color), CON_COLOR_WHITE, CON_COLOR_GREEN);
	con_initPair(short(Palette::predator_color), CON_COLOR_RED, CON_COLOR_GREEN);
}


ConsoleView::~ConsoleView()
{
	con_clearScr();
}


void ConsoleView::initial_view() const
{
	int width = this->_map.get_width();
	int height = this->_map.get_height();

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			paint(x, y, empty_view, Palette::field_color);
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
				clr = Palette::plant_color;
				break;

			case LifeObject::Type::herbivorous:
				chr = herbivorous_view;
				clr = Palette::herbivorous_color;
				break;

			case LifeObject::Type::predator:
				chr = predator_view;
				clr = Palette::predator_color;
				break;

			default:
			case LifeObject::Type::none:
				chr = empty_view;
				clr = Palette::field_color;
				break;
		}
	}
	else
	{
		chr = 'x';
		clr = Palette::border_color;
	}

	paint(obj_pos['x'], obj_pos['y'], chr, clr);
}


void ConsoleView::paint(int x, int y, char chr, const Palette &clr) const
{
	con_gotoXY(x, y);
	con_setColor(short(clr));
	con_outTxt("%c", chr);
}


void ConsoleView::clear() const
{
	con_clearScr();
}


TextView::TextView(const PopulationMap &map)
	: AbstractView(map)
{
}


TextView::~TextView()
{
}


void TextView::initial_view() const
{
	con_clearScr();
	con_gotoXY(0, 0);
	con_outTxt("### MAP VIEW ###\n");
}


void TextView::render_object(const LifeObject &obj) const
{
	std::string type;
	switch (obj.get_type())
	{
		case LifeObject::Type::plant:
			type = "Plant";
			break;

		case LifeObject::Type::herbivorous:
			type = "Herbivorous";
			break;

		case LifeObject::Type::predator:
			type = "Predator";
			break;

		default:
		case LifeObject::Type::none:
			type = "None";
			break;
	}

	std::stringstream ss;
	ss << type << ": " << obj.get_health() << " " << obj.get_position();
	con_outTxt("%s\n", ss.str().c_str());
}
