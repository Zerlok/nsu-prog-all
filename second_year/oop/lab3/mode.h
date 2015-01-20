#ifndef __MODE_H__
#define __MODE_H__


/*
 * --------------- GAME MODE INTERFACE ---------------
 *
 * This class is an interface for other mode classess
 *
 * The Game class uses it.
 *
 */
class Mode
{
	public:
		Mode() {};
		virtual ~Mode() {};
		
		virtual void play() = 0;
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
		DetailedMode(
				const MatrixField **matrix,
				const std::string& configs_dir);
		
		~DetailedMode();

		virtual void play();

	private:
		// std::array<Strategy, 3> _strategies;
		Strategy **_strategies;
		StrategyFactory *_factory;
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
		FastMode(
				const MatrixField **matrix,
				const std::string& configs_dir);

		~FastMode();
		
		virtual void play();

	private:
		// std::array<Strategy, 3> _strategies;
		Strategy **_strategies;
		StrategyFactory *_factory;
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
		TournamentMode(
				const MatrixField **matrix,
				const std::string& configs_dir);

		~TournamentMode();
		
		virtual void play();

	private:
		// std::array<Strategy, 3> _strategies;
		Strategy **_strategies;
		StrategyFactory *_factory;
};


// __MODE_H__
#endif
