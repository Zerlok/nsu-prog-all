#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream> // cout, endl
#include <stdexcept> // throw
#include <fstream> // file << >>
#include <cstdlib> // atoi
#include <cstring> // strcpy, strlen
#include <string> // to_string
#include <unistd.h> // usleep, system


#define __DEBUG__
#define __DEBUG__LIFEFORM__
#define __DEBUG__UNIVERSE__
#define __DEBUG__CONSOLE__


static const char ALIVE_FORM = '@';
static const char DEAD_FORM = '.';
static const char ALIVE_FORM_FILE = '#';
static const char DEAD_FORM_FILE = '.';

static const int STD_UNIVERSE_SIZE = 36;
static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};


static const int SLEEP_MSEC = 120000; // 150000 - normal


enum ConsoleSignal
{
	START, // Start the game.

	SAVE, // Save universe to file.
	OPEN, // Open universe from file.
	TICK, // Play universe animation.
	HELP, // Show help message.
	EXIT, // Exit the game.

	UNKNOWN_CMD, // The input command is unknown.
	WAIT_CMD // Wait for the command.
};


enum LifeformState
{
	ALIVE, // Alive form.
	DEAD // Dead form.
};



/* -------------- MODELS -------------- */

class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		void set_neighbours_num(const int n);
		void set_state(const LifeformState state);
		void set_state_by_neighbours(
				const bool born_criteria[9],
				const bool survival_criteria[9]
		);

		bool is_alive() const;

	private:
		LifeformState _state;
		int _neighbours_num;
};


class Universe
{
	public:
		Universe(const std::string& filename);
		~Universe();

	private:
		Lifeform **_data;
		int _width;
		int _step;
		bool _born_criteria[9];
		bool _survival_criteria[9];
};


class Game
{
	public:

};


/* -------------- VIEWS -------------- */

class Display
{
public:
	Display();
	~Display();
	
};


/* -------------- CONTROLLERS -------------- */

class Console
{
	public:
		Console(int argc, char **argv);
		~Console();

		bool save(Universe& );
		bool open();
		bool tick();
		void help();

		bool is_saved();

		void run();

	private:
		/* Methods */
		bool _parse_line();
		void _parse_arguments();

		/* Fields */
		int _first_flag_num;
		int _argc;
		char **_argv;

		bool _online;
		bool _saved;

		int _steps_limit;
		Universe *_space;
		std::string _input_filename;
		std::string _output_filename;
		
		std::string _line;
};


// __LIFEGAME_H__
#endif
