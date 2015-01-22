#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>		// cout, endl.
#include <cstring>		// strcpy, strlen.
#include <string>		// string.
#include <vector>		// vector.
#include <iterator>		// ostream_iterator.
#include <algorithm>	// sort, find, all_of, for_each.
#include <iomanip>		// setw.
#include <map>			// map.
#include <sstream>		// istringstream.
#include <time.h>		// time for srand.


// --------------- DEBUG ---------------

static bool DEBUG = false;
static const char DBG_HEADER[] = "~ debug: ";
static const char DBG_ENABLED[] = "You have started this program with full debug!";


// --------------- ERRORS ---------------

static const char ERR_HEADER[] = "# error: ";

/*
 * Simple errors.
 */
static const char ERR_INTEGER_EXPECTED[] = " - the integer was expected!";
static const char ERR_TOO_BIG_INTEGER[] = " - too big integer!";

/*
 * Errors for input line.
 */
static const char ERR_UNKNOWN_FLAG[] = " flag is unknown!";
static const char ERR_UNKNOWN_ARGUMENT[] = " argument is unknown!";
static const char ERR_VALUE_EXPECTED[] = " expects the value!";
static const char ERR_INVALID_INPUT[] = " - invalid input! Try -h or --help to see how to start this program.";
static const char ERR_INVALID_MODE[] = " - invalid game mode!\n";
static const char ERR_INVLID_STRATEGIES_AMMOUNT[] = " - is invalid number of strategies (must be 3)";
static const char ERR_STRATEGIES_IS_NOT_ENOUGH[] = " - too few strategies (must be 3 or more)";

/*
 * Command Errors in foreground playing.
 */
static const char ERR_UNKNOWN_CMD[] = " command is unknown. Try help to see available commands.";


// --------------- WARNINGS ---------------

static const char WARNING_HEADER[] = "* warning: ";


// --------------- HELP MESSAGES ---------------

static const char HELP_DESCRIPTION[] = "Description:\n   Three (or more) men sits in the jail and everyone wants to escape from there.\n   Each can cooperate with others or betray them all.\n   And the only thing is matter - you should quit as soon as it possible...\n";
static const char HELP_USAGE[] = "Usage:\n   ./main [STRATEGIES] [FLAGS] [ARGUMENTS]\n   STRATEGIES - the names of strategies to play with (the number of strategies depends on mode you choose to play).\n";
static const char HELP_AVAILABLE_MODES[] = "Available mods:\n   detailed    - play and stare at huge volume of process information (requires 3 strategies)\n   fast        - just play and show the total scores (requires 3 strategies)\n   tournament  - in development \%)";
static const char HELP_FLAGS[] = "Flags and arguments:\n   -m, --mode     - select the mode [detailed|fast|tournament]\n   -s, --steps    - specify the number of iterations to play (game will running in background).\n   -x, --matrix   - specify the path to score matrix file.\n   -c, --configs  - specify the directory for strategies.\n   -h, --help     - shows this message\n";
static const char HELP_COMMANDS[] = "These commands are available:\n   list                 - show available strategies.\n   use <s1> <s2> <s3>   - play with another <s1>, <s2> and <s3> strategies.\n   tick <n>             - play <n> iterations.\n   clear                - clear the screen.\n   help                 - show this help message.\n   quit                 - end the game.\n";


// --------------- FOREGROUND STRINGS ---------------

static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into the Prisoners Dilemma Game (version 1.0 beta)!\nType the command below, or use 'help' to see available commands.";
static const char WARNING_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


// --------------- CONSTANTS ---------------

static const size_t MAX_INTEGER_LEN = 5;
static const size_t str_none = std::string::npos;


enum Decision
{
	defect = 0,
	cooperate = 1
};


typedef std::map< std::vector<Decision>, std::vector<int> > ScoreMatrix;


// --------------- STANDARD CONFIGURATION ---------------

static const int STD_STEPS_LIMIT = 0;
static const char STD_MODE_NAME[] = "detailed";
static const char STD_CONFIGS_PATH[] = "defaults";
static const char STD_MATRIX_PATH[] = "";


// --------------- EXTRA FUNCITONS ---------------

void show_matrix(const ScoreMatrix& matrix);
void show_str_vector(const std::vector<std::string> v);


// __MAIN_H__
#endif
