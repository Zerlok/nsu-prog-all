#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>

#define _DEBUG_ON

#define STRING_ARRAY_EXPANDING_CRITERIA 2
#define PROCESS_ARRAY_EXPANDING_CRITERIA 2


#define ARGS_LEN 256
#define LINE_LEN 256


#define STD_DUMP_FILENAME ".vshell_out"
#define CMD_EXIT "exit"
#define CMD_HELP "help"


#define LINE_START_SYMBOL ">>> "

#define LINE_SKIPPER_SYMBOL '\\'
#define LINE_SEPARATOR_SYMBOL ' '
#define LINE_DELIMITTER_SYMBOL '"'
#define LINE_TAB_SYMBOL '\t'
#define LINE_END_SYMBOL '\n'

#define LINE_INPUT_STREAM_STRING "<"
#define LINE_OUTPUT_STREAM_STRING ">"
#define LINE_APPEND_STREAM_STRING ">>"
#define LINE_BACKGROUND_STRING "&"
#define LINE_PIPE_STRING "|"


#define CODE_WAIT -1
#define CODE_SUCCESS 0
#define CODE_FAIL 1
#define CODE_EXIT 2
#define CODE_INVALID_CALL 4
#define CODE_UNKNOWN_CMD 5


extern char **environ;


// __MAIN_H__
#endif
