#ifndef __POPULATIONMAPVIEW_H__
#define __POPULATIONMAPVIEW_H__


#include "populationmap.h"


class AbstractView
{
	public:
		AbstractView(const PopulationMap& map);
		virtual ~AbstractView();

		virtual void render_map() const;
		virtual void initial_view() const = 0;
		virtual void render_object(const LifeObject &obj) const = 0;

	protected:
		const PopulationMap &_map;
};


class ConsoleView : public AbstractView
{
	public:
		// Static.
		static const char dead_view = '*';
		static const char empty_view = ' ';
		static const char plant_view = '!';
		static const char herbivorous_view = '&';
		static const char predator_view = '@';

		enum class Palette
		{
			dead_color = 1,
			field_color = 2,
			plant_color = 3,
			predator_color = 4,
			herbivorous_color = 5
		};

		// Constructors / Destructor.
		ConsoleView(const PopulationMap &map);
		virtual ~ConsoleView();

		// Methods.
		virtual void initial_view() const override;
		virtual void render_object(const LifeObject &obj) const override;

		void clear() const;

	private:
		void paint(int x, int y, char chr, const Palette &clr) const;
};


class TextView : public AbstractView
{
	public:
		TextView(const PopulationMap &map);
		virtual ~TextView();

		virtual void initial_view() const override;
		virtual void render_object(const LifeObject &obj) const override;
};


// __POPULATIONMAPVIEW_H__
#endif
