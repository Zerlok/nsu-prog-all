#ifndef __GAME_H__
#define __GAME_H__


/*
 * --------------- GAME SIGNALS ---------------
 *
 * This signals are maden for foreground playing.
 *
 */
enum GameSignal
{
	/*
	 * Main signals
	 */
	TICK_GAME,		// Play universe animation.
	CLEAR_SCREEN,	// Clear the console screen.
	EXIT_GAME,		// Exit the game.
	SHOW_HELP,		// Show help message.

	/* 
	 * Accessory signals
	 */
	START_GAME,		// Start the game.
	UNKNOWN_CMD,	// The input command is unknown.
	WAIT_CMD		// Wait for the command.
};


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
		Game(int argc, char **argv);
		~Game();

		/*
		 * Main methods
		 */
		void run();					// Start gameing

		/*
		 * Foreground methods
		 */
		bool tick(const int limit = 1);	// Make <n> iterations
		void clear_screen();		// Clear the console screen
		void help();				// Show help message

	private:
		/*
		 * Parsing methods
		 */
		void _parse_input(int argc, char **argv);	// Parse the input line
		bool _parse_cmd(const std::string cmd);	// Parse the input command (in foreground mode)

		bool _is_in_background;		// Is game playing in background.
		GameMode *_mode;			// The playing gamemode.
		int _steps_limit;
		std::string _configs_dir;
		std::string _matrix_file;
};


// __GAME_H__
#endif
