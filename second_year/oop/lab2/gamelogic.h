#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__


enum GameSignal
{
	SAVE_GAME, // Save universe to file.
	OPEN_GAME, // Open universe from file.
	TICK_GAME, // Tick universe steps.
	ANIM_GAME, // Show animation of universe ticking.
	SHOW_HELP, // Show help message.
	EXIT_GAME, // Exit the game.

	START_GAME, // Start the game.

	UNKNOWN_CMD, // The input command is unknown.
	WAIT_CMD // Wait for the next command.
};


class Game
{
	public:
		Game(int argc, char **argv);
		~Game();

		/* Methods */
		void save();
		void open();
		void tick();
		void animate();

		bool is_saved();

		void run();
		void help();

	private:
		/* Methods */
		void _parse_input(int argc, char **argv);
		bool _parse_command(const std::string& cmd);

		/* Fields */
		bool _debug;
		bool _is_valid_input;
		bool _online;
		bool _saved;

		int _steps_limit;
		Universe *_space;
		std::string _input_filename;
		std::string _output_filename;
};


// __GAMELOGIC_H__
#endif
