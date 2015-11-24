#ifndef __POPULATIONMAPVIEW_H__
#define __POPULATIONMAPVIEW_H__


#include "console.h"
#include "populationmap.h"


class PopulationMapView
{
	public:
		// Static.
		static const char default_empty_view = '.';
		static const char default_plant_view = 'l';
		static const char default_predator_view = 'p';
		static const char default_herbivorous_view = 'h';

		enum class Palette
		{
			border_color = 1,
			field_color = 2,
			plant_color = 3,
			predator_color = 4,
			herbivorous_color = 5
		};

		// Constructors / Destructor.
		PopulationMapView(char empty_view=default_empty_view,
				char plant_view=default_plant_view,
				char herbivorous_view=default_herbivorous_view,
				char predator_view=default_predator_view);
		~PopulationMapView();

		// Methods.
		void render(const PopulationMap &map) const;
		void render(const LifeObject &obj) const;

		void paint(int x, int y, char chr, const Palette &clr) const;
		void clear() const;

	private:
		// Fileds.
		char _empty_view;
		char _plant_view;
		char _herbivorous_view;
		char _predator_view;
};


// __POPULATIONMAPVIEW_H__
#endif
