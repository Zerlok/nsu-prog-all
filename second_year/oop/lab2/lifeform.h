#ifndef __LIFEFORM_H__
#define __LIFEFORM_H__


enum LifeformState
{
	ALIVE = 0, // Alive form.
	DEAD = 1 // Dead form.
};


class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		friend int operator+(
				int x,
				Lifeform& form);
		friend int operator+(
				const Lifeform& form1,
				const Lifeform& form2);

		void apply_state_by_criteria(
				const bool born_criteria[9],
				const bool survival_criteria[9]);
		
		void set_neighbours_num(const int n);
		void set_state(const LifeformState state);

		bool is_alive() const;
		
		bool born();
		bool kill();

	private:
		LifeformState _state;
		int _neighbours_num;
};

int operator+(
		int x,
		Lifeform& form);
int operator+(
		const Lifeform& form1,
		const Lifeform& form2);


// __LIFEFORM_H__
#endif
