#include "mod.h"

int main() {
	int cur_notation, new_notation = 0;
	int *lst;
	int i, len = 10;
	char numbers[LIMIT];

	scanf("%s %d %d", numbers, &cur_notation, &new_notation);
	lst = to_list_from_str(numbers);
	printf("%d\n", lst[0]);
	// for (i = 0; i < len; i++) {
	// 	printf("%d, ", lst[i]);
	// }
	printf("\n");
	return 0;
}