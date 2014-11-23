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
class GameMode
{
	public:
		virtual ~GameMode() {};

		virtual void play() = 0;
};


/*
 * --------------- DETAILED MODE CLASS ---------------
 *
 * This class describes the detailed mode playing.
 *
 */
class DetailedMode : public GameMode
{
	public:
		DetailedMode();
		~DetailedMode();

		virtual void play();
};


/*
 * --------------- FAST MODE CLASS ---------------
 *
 * This class describes the fast mode playing.
 *
 */
class FastMode : public GameMode
{
	public:
		FastMode();
		~FastMode();
		
		virtual void play();
};


/*
 * --------------- TOURNAMENT MODE CLASS ---------------
 *
 * This class describes the tournament mode playing.
 *
 */
class TournamentMode : public GameMode
{
	public:
		TournamentMode();
		~TournamentMode();
		
		virtual void play();
};


// __MODE_H__
#endif
