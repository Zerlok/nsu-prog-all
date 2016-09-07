#ifndef __POPULATIONMAPVIEW_H__
#define __POPULATIONMAPVIEW_H__


#include <fstream>
#include "populationmap.h"


class AbstractView
{
	public:
		AbstractView(const PopulationMap& map);
		virtual ~AbstractView();

		virtual void initialize_map_view() const = 0;
		virtual void render_map() const;
		virtual void render_object(const LifeObject *obj) const = 0;
		virtual void clear_map() const = 0;

	protected:
		const PopulationMap &_map;
};


class ConsoleView : public AbstractView
{
	public:
		// Static.
		static const char dead_view = '*';
		static const char empty_view = ' ';
//		static const char plant_view = '`';
		static const char herbivorous_view = '&';
		static const char predator_view = '@';

		enum class Palette
		{
			text = 1,
			field,
			dead,
			plant,
			herbivorous,
			predator,
		};

		// Constructors / Destructor.
		ConsoleView(const PopulationMap &map);
		virtual ~ConsoleView();

		// Methods.
		virtual void initialize_map_view() const override;
		virtual void render_map() const override;
		virtual void render_object(const LifeObject *obj) const override;
		virtual void clear_map() const override;

		void clear_object(const LifeObject *obj) const;
		char get_plant_view(const LifeObject *plant) const;

	private:
		void paint(int x, int y, char chr, const Palette &clr) const;
};


class TextView : public AbstractView
{
	public:
		TextView(const PopulationMap &map, std::ostream &out);
		virtual ~TextView();

		virtual void initialize_map_view() const override;
		virtual void render_object(const LifeObject *obj) const override;
		virtual void clear_map() const override;

	private:
		std::ostream &_out;
};


// __POPULATIONMAPVIEW_H__
#endif
