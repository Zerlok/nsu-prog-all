#include <stdio.h>
#include <string.h>
#define LIMIT 100
#define DIGITS {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
#define SYMBOLS {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}

int to_x_from_a(char num[LIMIT], int cur_notation, int new_notation);
