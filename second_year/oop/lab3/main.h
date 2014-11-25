#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>		// cout, endl.
#include <cstring>		// strcpy, strlen.
#include <string>		// string
#include <sys/stat.h>	// floder info


// --------------- ERRORS ---------------

#define CONSOLE static const char

CONSOLE ERR_HEADER[] = "### Error ###\n";

/*
 * Simple errors.
 */
CONSOLE ERR_INTEGER_EXPECTED[] = " - an integer was expected!";
CONSOLE ERR_TOO_BIG_INTEGER[] = " - too big integer.";
CONSOLE ERR_NEGATIVE_VALUE[] = " - must be grater or equals 0!";

/*
 * Errors for input line.
 */
CONSOLE ERR_UNKNOWN_FLAG[] = " - unknown flag.";
CONSOLE ERR_UNKNOWN_ARGUMENT[] = " - unknown argument.";
CONSOLE ERR_VALUE_EXPECTED[] = " - the value was expected!";
CONSOLE ERR_INVALID_INPUT[] = " - invalid input. Try -h or --help to see how to start this program.";
CONSOLE ERR_INVALID_MODE[] = " - invalid game mode. Available modes are:\n   detailed    - ...\n   fast        - ...\n   tournament  - ...";
CONSOLE ERR_PATH_NOT_ACCESSABLE[] = " - permission denied or not exists!";

/*
 * Errors in foreground playing.
 */
CONSOLE ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help to see available commands.";

// --------------- WARNINGS ---------------

CONSOLE WARNING_HEADER[] = "*** Warning ***\n";
CONSOLE DEBUG_ENABLED[] = "You started this program with full debug!";


// --------------- HELP MESSAGES ---------------

CONSOLE HELP_USAGE[] = "(-h, --help)";
CONSOLE HELP_COMMANDS[] = "These commands are available:\n   tick <n=1>  - play <n> iterations.\n   clear       - clear the console screen.\n   help        - show this help.\n   quit        - exit the game.";


// --------------- FOREGROUND STRINGS ---------------

CONSOLE CMD_IN[] = "> ";
CONSOLE MSG_GREETING[] = "Welcome into the Game (version 0.001 alpha)!\nType a command below, or use 'help' to see available commands.";
CONSOLE WARNING_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


// --------------- CONSTANTS ---------------

static const size_t MAX_INTEGER_LEN = 5;


// --------------- INCLUDE MY MODULES ---------------

#include "mode.h"
#include "game.h"


enum MODULE
{
	GAME,
	MODE,

	MAIN
};


// --------------- STANDARD CONFIGURATION ---------------

typedef DetailedMode STD_MODE;

static const int STD_STEPS_LIMIT = 0;
CONSOLE STD_CONFIGS_DIR[] = "defaults";
CONSOLE STD_MATRIX_FILE[] = "defaults/matrix";


// __MAIN_H__
#endif
