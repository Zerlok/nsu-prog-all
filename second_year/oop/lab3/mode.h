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
		virtual ~Mode() {
			if (DEBUG) std::cout
					<< "Deleting the mode interface..."
					<< std::endl;
		}

		virtual void clear() = 0;
		
		virtual bool use(
				const std::vector<std::string>& strategy_names) = 0;

		virtual std::vector<std::string> get_available_strategies_names() const = 0;
		virtual std::vector<std::string> get_current_strategies_names() const = 0;
		virtual std::vector<int> get_scores() const = 0;

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
				const StrategyFactory& factory,
				const std::vector<std::string>& names,
				const ScoreMatrix& matrix,
				const std::string& configs_dir);
		
		~DetailedMode() {
			if (DEBUG) std::cout
					<< "Destroying the DetailedMode..."
					<< std::endl;
		}

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual std::vector<std::string> get_available_strategies_names() const;
		virtual std::vector<std::string> get_current_strategies_names() const;
		virtual std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;

		const StrategyFactory _factory;
		const ScoreMatrix _matrix;
		const std::string _configs_dir;
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
				const StrategyFactory& factory,
				const std::vector<std::string>& names,
				const ScoreMatrix& matrix,
				const std::string& configs_dir);

		~FastMode() {
			if (DEBUG) std::cout
					<< "Destroying the FastMode..."
					<< std::endl;
		}

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual std::vector<std::string> get_available_strategies_names() const;
		virtual std::vector<std::string> get_current_strategies_names() const;
		virtual std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;

		const StrategyFactory& _factory;
		const ScoreMatrix _matrix;
		const std::string& _configs_dir;
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
				const StrategyFactory& factory,
				const std::vector<std::string>& names,
				const ScoreMatrix& matrix,
				const std::string& configs_dir);

		~TournamentMode() {
			if (DEBUG) std::cout
					<< "Destroying the TournamentMode..."
					<< std::endl;
		}

		virtual void clear();

		virtual bool use(
				const std::vector<std::string>& strategy_names);

		virtual std::vector<std::string> get_available_strategies_names() const;
		virtual std::vector<std::string> get_current_strategies_names() const;
		virtual std::vector<int> get_scores() const;

		virtual bool is_registered(
				const std::string& strategy_name) const;

		virtual bool are_registered(
				const std::vector<std::string>& strategy_names) const;

		virtual void play(int limit = 1);

	private:
		std::vector<int> _scoretable;
		std::vector<std::string> _names;
		std::vector<Strategy *> _strategies;

		const StrategyFactory& _factory;
		const ScoreMatrix _matrix;
		const std::string& _configs_dir;
};


// __MODE_H__
#endif
