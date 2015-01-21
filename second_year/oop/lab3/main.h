#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>		// cout, endl.
#include <cstring>		// strcpy, strlen.
#include <string>		// string.
#include <vector>		// vector.
#include <iterator>		// ostream_iterator.
#include <map>			// map.
#include <time.h>		// time for srand.


// --------------- ERRORS ---------------

static const char ERR_HEADER[] = "# Error: ";

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


// --------------- DEBUG ---------------

static const char DBG_HEADER[] = "~ Debug: ";
static const char DBG_ENABLED[] = "You started this program with full debug!";


// --------------- WARNINGS ---------------

static const char WARNING_HEADER[] = "! Warning: ";


// --------------- HELP MESSAGES ---------------

static const char HELP_USAGE[] = "(-h, --help)";
static const char HELP_COMMANDS[] = "These commands are available:\n   tick <n=1>  - play <n> iterations.\n   clear       - clear the static const char screen.\n   help        - show this help.\n   quit        - exit the game.";


// --------------- FOREGROUND STRINGS ---------------

static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into the Game (version 0.001 alpha)!\nType a command below, or use 'help' to see available commands.";
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
static const char STD_CONFIGS_DIR[] = "defaults";
static const char STD_MATRIX_FILE[] = "defaults/matrix";


// __MAIN_H__
#endif
