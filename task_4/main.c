#include "mod.h"

int main() {
	int cur_notation, new_notation = 0;
	int *lst;
	int i, len;
	char numbers[LIMIT] = {0};
	scanf("%s %d %d", &numbers, &cur_notation, &new_notation);
	// lst, len = to_list_from_str(numbers);
	printf("%d %d\n", to_list_from_str(numbers));
	printf("%d\n", lst[0]);
	for (i = 0; i < len; i++) {
		printf("%d, ", lst[i]);
	}
	// printf("%s", numbers);
	// printf("%d", lst);
	// printf("%d", check_notation(numbers, cur_notation));
	// printf("%d", (int)'0');
	printf("\n");
	return 0;
}