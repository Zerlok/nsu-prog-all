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
		void help();				// Show help message

	private:
		/*
		 * Private methods
		 */
		void _parse_input();		// Parse the input line
		bool _parse_cmd();			// Parse the input command (in foreground mode)

		/*
		 * Private fields
		 */
		int _argf;					// The number of first flag.
		int _argc;					// The number of input values.
		char **_argv;				// The input values.

		bool _is_in_background;		// Is game playing in background.

		GameMode *_mode;			// The playing gamemode.

		std::string _cmd;			// The input command (foreground mode)
};


// __GAME_H__
#endif
