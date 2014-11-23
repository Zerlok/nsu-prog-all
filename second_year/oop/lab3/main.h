#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>		// cout, endl.
#include <cstring>		// strcpy, strlen.
#include <string>		// std::string


/*
 * --------------- DEBUG ---------------
 */

#define __DEBUG__MAIN__
#define __DEBUG__GAME__
#define __DEBUG__GAMEMODE__


/*
 * --------------- ERRORS MESSAGES ---------------
 */

static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [size])!";

static const char ERR_NOT_ENOUGH_VALUES[] = "Not enough values for arguments.";
static const char ERR_NO_VALUE[] = "The command value was expected.";
static const char ERR_UNKNOWN_FLAG[] = "Unknown flag. Try -h or --help to see available flags.";
static const char ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help to see available commands.";
static const char ERR_NO_FLAGS[] = "Please, write flags or arguments.";


/*
 * --------------- HELP MESSAGES ---------------
 */

static const char HELP_DESCRIPTION[] = "\n";
static const char HELP_USAGE[] = "\n";
static const char HELP_FLAGS[] = "\n";
static const char HELP_COMMANDS[] = "These commands are available:\n   tick <n=1> - play <n> iterations.\n   help - show this help.\n   quit - exit the game.";


/*
 * --------------- FOREGROUND STRINGS ---------------
 */

static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into the Game (version 0.001 alpha)!\nType a command below, or use 'help' to see available commands.";
static const char WARNING_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


/*
 * --------------- STANDARD STRINGS ---------------
 */

static const char STD_INPUT_FILENAME[] = "demo/demo1.life";
static const char STD_OUTPUT_FILENAME[] = "output.life";


/*
 * --------------- INCLUDE MY MODULES ---------------
 */
#include "mode.h"
#include "game.h"


// __MAIN_H__
#endif
