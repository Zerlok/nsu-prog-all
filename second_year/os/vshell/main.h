#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


#define STRING_ARRAY_EXPANDING_CRITERIA 2
#define CMD_ARRAY_EXPANDING_CRITERIA 2

#define ARGS_LEN 256
#define LINE_LEN 256


#define STD_DUMP_FILENAME "vshel.out"
#define CMD_EXIT "exit"


#define LINE_START_SYMBOL ">>> "
#define LINE_SKIP_SYMBOL '\\'
#define LINE_SEPARATOR_SYMBOL ' '
#define LINE_DELIMITTER_SYMBOL '"'
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
#define CODE_UNKNOWN_CMD 3


// For debug only
static int DEBUG = 1;


// __MAIN_H__
#endif