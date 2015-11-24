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
}


PopulationMapView::~PopulationMapView()
{
}


void PopulationMapView::render(const PopulationMap &map) const
{
	for (const LifeObject *obj : map.get_objects())
		render(*obj);
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
}


void PopulationMapView::clear() const
{
}
