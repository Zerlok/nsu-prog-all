#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Constants

#define NUM_END -1 // The end of array
#define MIN_NOTATION 2 // Minimal notation
#define LIMIT 100 // Max cells in array
#define WORD_DIFF 55 // A - Z
#define DIGIT_DIFF 48 // 0 - 9

// Error Constants

#define ERR_UNKNOWN 0
#define ERR_NOTATION 100
#define ERR_SYMBOL 200
#define ERR_DIGIT 300

char *get_number_in_new_notation(char *num, int cur_notation, int new_notation);
