#ifndef __UNIVERSE_H__
#define __UNIVERSE_H__


class Universe
{
	public:
		Universe(
				const int length = STD_UNIVERSE_SIZE,
				const bool born_criteria[9] = STD_BORN_CRITERIA,
				const bool survival_criteria[9] = STD_SURVIVAL_CRITERIA);

		~Universe();

		Universe(const std::string& filename);
		void write_to_file(const std::string& filename) const;

		bool init(
				const int x,
				const int y,
				const LifeformState state = ALIVE);

		Lifeform& get(const int x, const int y) { return _data[x][y]; }

		int count_neighbours(const int x, const int y) const;
		size_t count_alive_forms() const;

		void do_step();
		void draw() const;

	private:
		Lifeform **_data;
		int _width;
		int _step;
		bool _born_criteria[9];
		bool _survival_criteria[9];
};


// __UNIVERSE_H__
#endif
