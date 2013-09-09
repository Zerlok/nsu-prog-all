#include "mod.h"

int main() {
	int cur_notation, new_notation = 0;
	char number[100];
	scanf("%s %d %d", &str, &cur_notation, &new_notation);
	printf("%s", str);
	printf("%d", check_notation(number, cur_notation));
	//printf("%d", (int)'0');
	printf("\n");
}