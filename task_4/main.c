#include "mod.h"

int main(int argc, char const *argv[]) {
	int cur_notation, new_notation = 0;
	char number[LIMIT];

	scanf("%s %d %d", number, &cur_notation, &new_notation);
	get_number_in_new_notation(number, cur_notation, new_notation);
	printf("\n");
	return 0;
}