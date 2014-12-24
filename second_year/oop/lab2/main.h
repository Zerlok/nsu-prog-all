#ifndef __MAIN_H__
#define __MAIN_H__


#include <cstdlib> // atoi
#include <cstring> // strcpy, strlen
#include <fstream> // file << >>
#include <iostream> // cout, endl
#include <stdexcept> // throw
#include <string> // string, substr, find, size, c_str
#include <unistd.h> // usleep, system
#include <vector> // vector 


/*
 * Output headers.
 */
static const char DBG_HEADER[] = "~ Debug: ";
static const char ERR_HEADER[] = "# Error: ";


/*
 * Error messages.
 */
static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size mustbe grater than 1!";

static const char ERR_CMD_VALUE_EXPECTED[] = " - value was expected.";
static const char ERR_ARG_VALUE_EXPECTED[] = " - argument expects a value.";
static const char ERR_FLAG_VALUE_EXPECTED[] = " - flag expects a value.";
static const char ERR_UNKNOWN_ARGUMENT[] = " - unknown argument. Try -h or --help.";
static const char ERR_UNKNOWN_FLAG[] = " - unknown flag. Try -h or --help.";
static const char ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help.";
static const char ERR_INVALID_INPUT[] = "Input is invalid. Game was stopped!";


static const char HELP_DESCRIPTION[] = "Description:\n   This is a simple cell's lyfecycle emulator was written on C++.\n   Note that the developer hate this programming language, so you may will find\n   some bugs :3\n\n";
static const char HELP_USAGE[] = "Usage:\n   lifegame [input_file] [flags]\n   - input_file - the name of start game file.\n\n";
static const char HELP_FLAGS[] = "These flags and arguments are available:\n   -i <int>, --iterations=<int>		- set the number of iterations.\n   -o <string>, --output=<string>	- set the name of output file.\n   -h, --help						- show help.\n";
static const char HELP_COMMANDS[] = "* These commands are available:\n*   save <filename>   - save the current game into file.\n*   open <filename>   - open the game from file.\n*   tick <n>          - make <n> iterations (will show you the result of <n> iterations).\n*   animate <n>       - play <n> iterations (will play an animation of <n> iterations).\n*   help              - show this help.\n*   exit              - exit the game.";


static const char CMD_IN[] = "> ";
static const char MSG_DEBUG_ENABLED[] = "Debug was enabled!";
static const char MSG_GREETING[] = "Welcome into Life Game (version 1.01)!\nType a command below, or use 'help' to see available commands.";
static const char MSG_SAVED[] = "The universe was saved successfully.";
static const char MSG_OPEND[] = "The universe was opened successfully.";
static const char MSG_WRITE_FILENAME[] = "Write the filname to save the game: ";
static const char MSG_NOT_SAVED_GAME[] = "Your current game is not saved, do you want to save it? (yes/no): ";
static const char MSG_YES_NO_ONLY[] = "Type 'yes' or 'no': ";
static const char MSG_STD_UNIVERSE_OPENED[] = "The demo game was opened from ";


static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';

static const char ALIVE_FORM_FILE = '#';
static const char DEAD_FORM_FILE = '.';


static const int SLEEP_MSEC = 120000; // 150000 - normal


/*
 * Standard properties
 */
static const int STD_UNIVERSE_SIZE = 36;
static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};
static const char STD_INPUT_FILENAME[] = "demo/demo1.life";
static const char STD_OUTPUT_FILENAME[] = "life.out";


/*
 * Constants
 */
static const size_t str_none = std::string::npos;


// __MAIN_H__
#endif
