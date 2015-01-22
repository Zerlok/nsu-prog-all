#ifndef __GAME_H__
#define __GAME_H__


/*
 * --------------- GAME CLASS ---------------
 *
 * Game class is a main class to run a game,
 * show help messages, describe the game,
 * show how to play and etc.
 *
 */
class Game
{
	public:
		Game(
				const int argc,
				const char **argv,
				const StrategyFactory& factory);

		~Game();

		/*
		 * Main methods
		 */
		void run();					// Start gameing

		/*
		 * Foreground methods (commands)
		 */
		void cmd_use(const std::vector<std::string>& names);	// Use specified strategies
		void cmd_list();			// Show the list of registered strategies
		void cmd_tick();			// Make iterations
		void cmd_clear();			// Clear the console screen
		void cmd_help();			// Show help message

		void show_scores();

	private:
		/*
		 * Parsing methods
		 */
		void _parse_input(const int argc, const char **argv);	// Parse the input line
		bool _parse_cmd(const std::string& cmd);	// Parse the input command (in foreground mode)
		ScoreMatrix _parse_matrix_file(const std::string& filename);

		bool _debug;
		bool _is_valid_input;
		bool _is_in_background;		// Is game playing in background.

		std::vector<std::string> _init_names;
		int _steps_limit;
		Mode *_mode;				// The playing gamemode.

		std::string _mode_name;
		std::string _matrix_path;
		std::string _configs_path;
};


// __GAME_H__
#endif
