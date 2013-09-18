#include "mod.h"

int main() {
	int cur_notation, new_notation = 0;
	char number[LIMIT];

	scanf("%s %d %d", number, &cur_notation, &new_notation);
	to_new_notation_from_curr(number, cur_notation, new_notation);
	printf("\n");
	return 0;
}