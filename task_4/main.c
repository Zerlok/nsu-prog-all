#include "mod.h"

int main() {
	int cur_notation, new_notation = 0;
	int * lst[10];
	int i;
	char numbers[LIMIT];
	scanf("%s %d %d", &numbers, &cur_notation, &new_notation);
	lst = to_list_from_str(numbers);
	for (i = 0; i < 100; i++) {
		printf("%d, ", lst[i]);
	}
	// printf("%s", numbers);
	// printf("%d", lst);
	// printf("%d", check_notation(numbers, cur_notation));
	// printf("%d", (int)'0');
	printf("\n");
	return 0;
}