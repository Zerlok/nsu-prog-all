#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>		// cout, endl.
#include <cstring>		// strcpy, strlen.
#include <string>		// string
#include <sys/types.h>	// folder
#include <sys/stat.h>	// floder info


// --------------- DEBUG ---------------

#define __DEBUG__MAIN__
#define __DEBUG__GAME__
#define __DEBUG__GAMEMODE__


// --------------- ERRORS ---------------

#define CONSOLE static const

CONSOLE char ERR_HEADER[] = "Error: ";

/*
 * Simple errors.
 */
CONSOLE char ERR_INTEGER_EXPECTED[] = " - an integer was expected!";
CONSOLE char ERR_TOO_BIG_INTEGER[] = " - too big integer.";
CONSOLE char ERR_NEGATIVE_VALUE[] = " - must be grater or equals 0!";
// static const char ERR_INDEX_OUT_RANGE[] = " - index is out of range (0 <= [index] < [size])!";

/*
 * Errors for input line.
 */
CONSOLE char ERR_UNKNOWN_FLAG[] = " - unknown flag.";
CONSOLE char ERR_UNKNOWN_ARGUMENT[] = " - unknown argument.";
CONSOLE char ERR_VALUE_EXPECTED[] = " - the value was expected!";
CONSOLE char ERR_INVALID_INPUT[] = " - invalid input. Try -h or --help to see how to start this program.";
CONSOLE char ERR_INVALID_MODE[] = " - invalid game mode. Available modes are:\n   detailed    - ...\n   fast        - ...\n   tournament  - ...";
CONSOLE char ERR_PATH_NOT_ACCESSABLE[] = " - permission denied!";
CONSOLE char ERR_PATH_NOT_EXISTS[] = " - not exists!";

/*
 * Errors in foreground playing.
 */
// CONSOLE char ERR_NO_VALUE[] = "The command value was expected.";
CONSOLE char ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help to see available commands.";

// --------------- WARNINGS ---------------

CONSOLE char WARNING_HEADER[] = "Warning: ";

// --------------- HELP MESSAGES ---------------

CONSOLE char HELP_DESCRIPTION[] = "(description)";
CONSOLE char HELP_USAGE[] = "(usage)";
CONSOLE char HELP_FLAGS[] = "(flags help)";
CONSOLE char HELP_COMMANDS[] = "These commands are available:\n   tick <n=1>  - play <n> iterations.\n   clear       - clear the console screen.\n   help        - show this help.\n   quit        - exit the game.";


// --------------- FOREGROUND STRINGS ---------------

CONSOLE char CMD_IN[] = "> ";
CONSOLE char MSG_GREETING[] = "Welcome into the Game (version 0.001 alpha)!\nType a command below, or use 'help' to see available commands.";
CONSOLE char WARNING_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


// --------------- CONSTANTS ---------------

CONSOLE size_t MAX_INTEGER_LEN = 5;


// --------------- INCLUDE MY MODULES ---------------

#include "mode.h"
#include "game.h"


// --------------- STANDARD CONFIGURATION ---------------

typedef DetailedMode STD_MODE;

CONSOLE int STD_STEPS_LIMIT = 0;
CONSOLE char STD_CONFIGS_DIR[] = "default";
CONSOLE char STD_MATRIX_FILE[] = "default/matrix";


// __MAIN_H__
#endif
