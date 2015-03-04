#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


#define STD_DUMP_FILENAME "vshel.dump"

#define ARRAY_EXPANDING_CRITERIA 2
#define CMD_EXPANDING_CRITERIA 2

#define ARGS_BUFF 256
#define LINE_BUFF 256
#define LINE_SEPARATOR_SYMBOL ' '
#define LINE_INPUT_STREAM_SYMBOL '<'
#define LINE_OUTPUT_STREAM_SYMBOL '>'
#define LINE_APPEND_STREAM_SYMBOL '>>'
#define LINE_BACKGROUND_SYMBOL '&'
#define LINE_PIPE_SYMBOL '|'
#define LINE_DELIMITTER_SYMBOL '"'
#define LINE_END_SYMBOL '\n'

#define CODE_EXIT -1
#define CODE_WAIT 0
#define CODE_SUCCESS 1
#define CODE_UNKNOWN_CMD 2


// For debug only
static int DEBUG = 1;


// __MAIN_H__
#endif