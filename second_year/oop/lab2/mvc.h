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

static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};

static const int SLEEP_MSEC = 120000; // 150000 - normal


enum GameMode
{
	ONLINE,
	OFFLINE
};

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


enum CellState
{
	ALIVE, // Alive form.
	DEAD // Dead form.
};


typedef struct universe_size
{
	int width;
	int height;
} UniverseSize;

static const UniverseSize STD_UNIVERSE_SIZE = {36, 36};


/* -------------- MODELS -------------- */

class Cell
{
	public:
		Cell(const CellState state = DEAD);
		~Cell();

		bool is_alive() const;

		void set_state(const CellState state);
		void set_neighbours_num(const int n);
		void set_state_by_neighbours(
				const bool born_criteria[9],
				const bool survival_criteria[9]
		);

		CellState& operator=(const CellState state);

	private:
		CellState _state;
		int _neighbours_num;
};


class Universe
{
	public:
		Universe(
				const UniverseSize size& = STD_UNIVERSE_SIZE,
				const bool born_criteria[9] = STD_BORN_CRITERIA,
				const bool survival_criteria[9] = STD_SURVIVAL_CRITERIA
		);
		~Universe();

		UniverseSize get_size() const;
		int get_step() const;

		Cell *get(const int x, const int y);
		Cell& operator[](const int x, const int y);

	private:
		Cell **_data;
		UniverseSize _size;
		bool _born_criteria[9];
		bool _survival_criteria[9];
		int _step;
};


class Game
{
	public:
		Game(const GameMode mode);
		~Game();

		const GameMode get_mode() const;
		Universe& get_universe() const;

		void reset_universe(Universe *new_space);

	private:
		const GameMode _mode;
		Universe *_space;
};


/* -------------- VIEWS -------------- */

class Display
{
	public:
		Display();
		~Display();

		void help();
};


/* -------------- CONTROLLERS -------------- */

class GameLogic
{
	public:
		GameLogic();
		~GameLogic();

		void save(
				const Universe& space,
				const std::string& filename
		) const;
		
		void open(
				const std::string& filename
		);
		
		void tick(
				const int iterations_limit
		);

		bool is_saved(
				const Universe& space
		) const;

		void parse_arguments();
		bool parse_line();

	private:
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
