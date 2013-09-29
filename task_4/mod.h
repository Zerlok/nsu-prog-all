#include <stdio.h>
#include <string.h>

// Constants

#define NUM_END -1
#define LIMIT 100
#define DIGITS {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
#define SYMBOLS '012356789ABCDEF'

#define WORD_DIFF 55
#define DIGIT_DIFF 48

// Errors Constants

#define ERR_UNKNOWN 0
#define ERR_NOTATION -100
#define ERR_SYMBOL -200
#define ERR_DIGIT -300

int get_number_in_new_notation(char *num, int cur_notation, int new_notation);
