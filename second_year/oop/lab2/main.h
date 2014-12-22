#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream> // cout, endl
#include <stdexcept> // throw
#include <fstream> // file << >>
#include <cstdlib> // atoi
#include <cstring> // strcpy, strlen
#include <string> // to_string
#include <unistd.h> // usleep, system


static const char DBG_HEADER[] = "~ Debug: ";
static const char ERR_HEADER[] = "# Error: ";

static const char ERR_NEGATIVE_VALUE[] = "The value must be grater or equal 0!";
static const char ERR_INDEX_OUT_RANGE[] = "Index is out of range (0 <= [index] < [universe size])!";
static const char ERR_BAD_UNIVERSE_SIZE[] = "The universe size mustbe grater than 1!";

static const char ERR_NOT_ENOUGH_VALUES[] = "Not enough values for arguments.";
static const char ERR_VALUE_EXPECTED[] = "The command value was expected.";
static const char ERR_UNKNOWN_FLAG[] = "Unknown flag. Try -h or --help to see available flags.";
static const char ERR_UNKNOWN_COMMAND[] = "Unknown command. Try help to see available commands.";
static const char ERR_NO_FLAGS[] = "Please, write flags or arguments.";


static const char HELP_DESCRIPTION[] = "Description:\n   This is a simple cell's lyfecycle emulator was written on C++.\n   Note that the developer hate this programming language, so you may will find\n   some bugs :3\n\n";
static const char HELP_USAGE[] = "Usage:\n   lifegame [input_file] [flags]\n   - input_file - the name of start game file.\n\n";
static const char HELP_FLAGS[] = "These flags are available:\n   -i <int>, --iterations=<int>		- set the number of iterations.\n   -o <string>, --output=<string>	- set the name of output file.\n   -h, --help						- show help.\n";
static const char HELP_COMMANDS[] = "These commands are available:\n   save <filename> - save the current game into file.\n   open <filename> - open the game from file.\n   tick <n> - play <n> iterations.\n   help - show this help.\n   exit - exit the game.";


static const char CMD_IN[] = "> ";
static const char MSG_GREETING[] = "Welcome into Life Game (version 1.01)!\nType a command below, or use 'help' to see available commands.";
static const char MSG_SAVED[] = "The universe was saved successfully.";
static const char MSG_OPEND[] = "The universe was opend successfully.";
static const char MSG_WRITE_FILENAME[] = "Write the filname to save the game: ";
static const char MSG_NOT_SAVED_GAME[] = "Your current game is not saved, do you want to save it? (yes/no): ";
static const char MSG_YES_NO_ONLY[] = "Type 'yes' or 'no': ";


static const char STD_INPUT_FILENAME[] = "demo/demo1.life";
static const char STD_OUTPUT_FILENAME[] = "life.out";


static const char ALIVE_FORM = 'o';
static const char DEAD_FORM = ' ';

static const char ALIVE_FORM_FILE = '#';
static const char DEAD_FORM_FILE = '.';


static const int SLEEP_MSEC = 120000; // 150000 - normal


static const bool STD_BORN_CRITERIA[9] = {false, false, false, true, false, false, false, false, false};
static const bool STD_SURVIVAL_CRITERIA[9] = {false, false, true, true, false, false, false, false, false};
static const int STD_UNIVERSE_SIZE = 36;


typedef std::string::npos str_none

// __MAIN_H__
#endif
