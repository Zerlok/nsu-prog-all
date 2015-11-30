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
	for (const LifeObject &obj : this->_map.get_objects())
		render_object(obj);
}


ConsoleView::ConsoleView(const PopulationMap &map)
	: AbstractView(map)
{
	con_initPair(short(Palette::field_color), CON_COLOR_GREEN, CON_COLOR_GREEN);
	con_initPair(short(Palette::border_color), CON_COLOR_WHITE, CON_COLOR_BLUE);
    con_initPair(short(Palette::plant_color), CON_COLOR_RED, CON_COLOR_RED);
	con_initPair(short(Palette::predator_color), CON_COLOR_CYAN, CON_COLOR_RED);
}


ConsoleView::~ConsoleView()
{
//	con_clearScr();
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
	paint(
			obj_pos['x'],
			obj_pos['y'],
			(obj.is_alive()
				? predator_view
				: empty_view),
			(obj.is_alive()
				? Palette::predator_color
				: Palette::field_color)
	);
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
	std::stringstream ss;
	ss << obj.get_position();
	con_outTxt("%s\n", ss.str().c_str());
}
