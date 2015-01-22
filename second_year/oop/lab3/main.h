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
static const char ERR_INTEGER_EXPECTED[] = " - an integer was expected!";
static const char ERR_TOO_BIG_INTEGER[] = " - too big integer.";
static const char ERR_NEGATIVE_VALUE[] = " - must be grater or equals 0!";

/*
 * Errors for input line.
 */
static const char ERR_UNKNOWN_FLAG[] = " - unknown flag.";
static const char ERR_UNKNOWN_ARGUMENT[] = " - unknown argument.";
static const char ERR_VALUE_EXPECTED[] = " - the value was expected!";
static const char ERR_INVALID_ARGUMENT[] = " - input argument is invalid.";
static const char ERR_INVALID_INPUT[] = " - invalid input. Try -h or --help to see how to start this program.";
static const char ERR_INVALID_MODE[] = " - invalid game mode. Available modes are:\n   detailed    - ...\n   fast        - ...\n   tournament  - ...";

/*
 * Command Errors in foreground playing.
 */
static const char ERR_CMD_VALUE_EXPECTED[] = " - the command value was expected!";
static const char ERR_UNKNOWN_CMD[] = "- the unknown command. Try help to see available commands.";


// --------------- WARNINGS ---------------

static const char WARNING_HEADER[] = "* warning: ";


// --------------- HELP MESSAGES ---------------

static const char HELP_DESCRIPTION[] = "(-h, --help)";
static const char HELP_USAGE[] = "none";
static const char HELP_FLAGS[] = "-h, --help  - shows this message";
static const char HELP_COMMANDS[] = "These commands are available:\n   //list    - sdfasdf\n   // use [<strategy 1>...]  - play <n> iterations.\n   tick <n>  - play <n> iterations.\n   clear       - clear the static const char screen.\n   help        - show this help message.\n   quit        - exit the game.";


// --------------- FOREGROUND STRINGS ---------------

static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into the Game (version 0.2 alpha pre-release)!\nType a command below, or use 'help' to see available commands.";
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

static const int STD_STEPS_LIMIT = 3;
static const char STD_MODE_NAME[] = "detailed";
static const char STD_CONFIGS_PATH[] = "defaults";
static const char STD_MATRIX_PATH[] = "";


// --------------- EXTRA FUNCITONS ---------------

void show_matrix(const ScoreMatrix& matrix);
void show_str_vector(const std::vector<std::string> v);


// __MAIN_H__
#endif
