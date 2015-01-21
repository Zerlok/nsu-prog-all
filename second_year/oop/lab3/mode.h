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

		virtual void clear() = 0;
		
		virtual bool use(
				const std::vector<std::string>& strategy_names) = 0;

		virtual const std::vector<std::string> get_available_strategies_names() const = 0;
		virtual const std::vector<std::string> get_current_strategies_names() const = 0;
		virtual const std::vector<int> get_scores() const = 0;

		virtual bool is_registered(
				const std::string& strategy_name) const = 0;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const = 0;

		virtual void play(int limit) = 0;
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
				const ScoreMatrix& matrix,
				const std::string& configs_dir);
		
		~DetailedMode();

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual const std::vector<std::string> get_available_strategies_names() const;
		virtual const std::vector<std::string> get_current_strategies_names() const;
		virtual const std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;
		const ScoreMatrix& _matrix;
		StrategyFactory _factory;
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
				const ScoreMatrix& matrix,
				const std::string& configs_dir);

		~FastMode();

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual const std::vector<std::string> get_available_strategies_names() const;
		virtual const std::vector<std::string> get_current_strategies_names() const;
		virtual const std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;
		const ScoreMatrix& _matrix;
		StrategyFactory _factory;
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
				const ScoreMatrix& matrix,
				const std::string& configs_dir);

		~TournamentMode();

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual const std::vector<std::string> get_available_strategies_names() const;
		virtual const std::vector<std::string> get_current_strategies_names() const;
		virtual const std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;
		const ScoreMatrix& _matrix;
		StrategyFactory _factory;
};


// __MODE_H__
#endif
