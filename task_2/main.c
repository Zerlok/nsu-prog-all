#include "mod.h"

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("------\n");
	printf("%d\n", get_gcd(a, b));
	return 0;
}
