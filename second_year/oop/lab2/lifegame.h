#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__


#include <iostream> // cout, endl
#include <stdexcept> // throw
#include <fstream> // file << >>
#include <cstdlib> // atoi
#include <cstring> // strcpy, strlen
#include <string> // to_string
#include <unistd.h> // usleep, system


// #define __DEBUG__
// #define __DEBUG__GAME__
// #define __DEBUG__UNIVERSE__
// #define __DEBUG__LIFEFORM__

static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size mustbe grater than 1!";

static const char ERR_NOT_ENOUGH_VALUES[] = "Not enough values for arguments.";
static const char ERR_NO_VALUE[] = "The command value was expected.";
static const char ERR_UNKNOWN_FLAG[] = "Unknown flag. Try -h or --help to see available flags.";
static const char ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help to see available commands.";
static const char ERR_NO_FLAGS[] = "Please, write flags or arguments.";


static const char HELP_DESCRIPTION[] = "Description:\n   This is a simple cell's lyfecycle emulator was written on C++.\n   Note that the developer hate this programming language, so you may will find\n   some bugs :3\n\n";
static const char HELP_USAGE[] = "Usage:\n   lifegame [input_file] [flags]\n   - input_file - the name of start game file.\n\n";
static const char HELP_FLAGS[] = "These flags are available:\n   -i <int>, --iterations=<int>		- set the number of iterations.\n   -o <string>, --output=<string>	- set the name of output file.\n   -h, --help						- show help.\n";
static const char HELP_COMMANDS[] = "These commands are available:\n   save <filename> - save the current game into file.\n   open <filename> - open the game from file.\n   tick <n> - play <n> iterations.\n   help - show this help.\n   exit - exit the game.";


static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into Life Game (version 1.00 beta)!\nType a command below, or use 'help' to see available commands.";
static const char MSG_SAVED[] = "The universe was saved successfully.";
static const char MSG_OPEND[] = "The universe was opend successfully.";
static const char MSG_WRITE_FILENAME[] = "Write the filname to save the game: ";
static const char WARNING_NOT_SAVED[] = "Your current game is not saved, do you want to save it? (yes/no): ";
static const char WARNING_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


static const char STD_INPUT_FILENAME[] = "demo/demo1.life";
static const char STD_OUTPUT_FILENAME[] = "output.life";


#ifndef __DEBUG__LIFEFORM__
static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';
#else
static const char ALIVE_FORM = '@';
static const char DEAD_FORM = '.';
#endif

static const char ALIVE_FORM_FILE = '#';
static const char DEAD_FORM_FILE = '.';

static const int SLEEP_MSEC = 120000; // 150000 - normal


enum GameSignal
{
	SAVE_GAME, // Save universe to file.
	OPEN_GAME, // Open universe from file.
	TICK_GAME, // Play universe animation.
	SHOW_HELP, // Show help message.
	EXIT_GAME, // Exit the game.

	START_GAME, // Start the game.

	UNKNOWN_CMD, // The input command is unknown.
	WAIT_CMD // Wait for the command.
};


enum LifeformState
{
	ALIVE, // Alive form.
	DEAD // Dead form.
};

static const int STD_UNIVERSE_SIZE = 36;
static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};


class Lifeform
{
	public:
		Lifeform(const LifeformState state = DEAD);
		~Lifeform();

		friend int operator+(int x, Lifeform& form);
		friend int operator+(const Lifeform& form1, const Lifeform& form2);

		void apply_state(const bool born_criteria[9],
						const bool survival_criteria[9]);
		void set_neighbours_num(const int n);
		void set_state(const LifeformState state);

		bool is_alive() const;
		
		bool born();
		bool kill();

	private:
		LifeformState _state;
		int _neighbours_num;
};

int operator+(int x, Lifeform& form);
int operator+(const Lifeform& form1, const Lifeform& form2);


class Universe
{
	public:
		Universe(const int length = STD_UNIVERSE_SIZE,
				const bool born_criteria[9] = STD_BORN_CRITERIA,
				const bool survival_criteria[9] = STD_SURVIVAL_CRITERIA
		);

		~Universe();

		Universe(const std::string& filename);
		void write_to_file(const std::string& filename) const;

		bool init(const int x, const int y, const LifeformState state = ALIVE);

		int count_neighbours(const int x, const int y) const;
		unsigned long long int count_all_alive_forms() const;

		void do_step();
		void draw() const;

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
		Game(int argc, char **argv);
		~Game();

		/* Methods */
		bool save();
		bool open();
		bool tick();
		bool is_saved();

		void run();
		void summarize();
		void help();

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
