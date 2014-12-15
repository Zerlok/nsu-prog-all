#ifndef __MODE_H__
#define __MODE_H__


/*
 * --------------- GAME MODE CLASS ---------------
 *
 * This class is an interface for other mode classess
 *
 * The Game class uses it.
 *
 */
class Mode
{
	public:
		virtual void play() = 0;
		virtual void setup(Strategy *s0, Strategy *s1, Strategy *s2) {};
};


/*
 * --------------- DETAILED MODE CLASS ---------------
 *
 * This class describes the detailed mode playing.
 *
 */
class DetailedMode : public Mode
{
	public:
		DetailedMode();
		~DetailedMode();

		virtual void play();
		
		virtual void setup(
				Strategy *s0,
				Strategy *s1,
				Strategy *s2
		);

	private:
		bool _debug;

		Strategy *_strategy_0;
		Strategy *_strategy_1;
		Strategy *_strategy_2;
};


/*
 * --------------- FAST MODE CLASS ---------------
 *
 * This class describes the fast mode playing.
 *
 */
class FastMode : public Mode
{
	public:
		FastMode();
		~FastMode();
		
		virtual void play();

	private:
		bool _debug;
};


/*
 * --------------- TOURNAMENT MODE CLASS ---------------
 *
 * This class describes the tournament mode playing.
 *
 */
class TournamentMode : public Mode
{
	public:
		TournamentMode();
		~TournamentMode();
		
		virtual void play();

	private:
		bool _debug;
};


// __MODE_H__
#endif
