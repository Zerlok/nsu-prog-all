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
		Game(const int argc, const char **argv);
		~Game();

		/*
		 * Main methods
		 */
		void run();					// Start gameing

		/*
		 * Foreground methods (commands)
		 */
		void cmd_tick();			// Make iterations
		void cmd_clear();			// Clear the console screen
		void cmd_help();			// Show help message

	private:
		/*
		 * Parsing methods
		 */
		void _parse_input(const int argc, const char **argv);	// Parse the input line
		bool _parse_cmd(const std::string& cmd);	// Parse the input command (in foreground mode)
		void _parse_matrix_file(const std::string& filename);

		bool _debug;
		bool _is_valid_input;

		bool _is_in_background;		// Is game playing in background.
		Mode *_mode;				// The playing gamemode.
		int _steps_limit;

		// std::array<MatrixField, 8> _matrix;
		MatrixField *_matrix;
		std::string _configs_dir;
		std::string _mode_str;
};


// __GAME_H__
#endif
