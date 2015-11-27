#include "console.h"
#include "populationmapview.h"


PopulationMapView::PopulationMapView(char empty_view,
				 char plant_view,
				 char herbivorous_view,
				 char predator_view)
	: _empty_view(empty_view),
	  _plant_view(plant_view),
	  _herbivorous_view(herbivorous_view),
	  _predator_view(predator_view)
{
	setenv("TERM", "xterm", 1);

	con_init();
	con_hideCursor();

	con_initPair(short(Palette::border_color), CON_COLOR_WHITE, CON_COLOR_BLUE);
	con_initPair(short(Palette::field_color), CON_COLOR_WHITE, CON_COLOR_GREEN);
	con_initPair(short(Palette::plant_color), CON_COLOR_RED, CON_COLOR_GREEN);
}


PopulationMapView::~PopulationMapView()
{
	con_clearScr();
	con_deinit();
}


void PopulationMapView::initial_view(const PopulationMap &map) const
{
	int width = map.get_width();
	int height = map.get_height();

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			paint(x, y, _empty_view, Palette::field_color);
}


void PopulationMapView::render(const PopulationMap &map) const
{
	for (const LifeObject &obj : map.get_objects())
		render(obj);
}


void PopulationMapView::render(const LifeObject &obj) const
{
	const Point &obj_pos = obj.get_position();
	paint(
			obj_pos['x'],
			obj_pos['y'],
			(obj.is_alive()
				? 'o'
				: '.'),
			(obj.is_alive()
				? Palette::plant_color
				: Palette::field_color)
	);
}


void PopulationMapView::paint(int x, int y, char chr, const Palette &clr) const
{
	con_gotoXY(x, y);
	con_setColor(short(clr));
	con_outTxt(" %c", chr);
}


void PopulationMapView::clear() const
{
	con_clearScr();
}
