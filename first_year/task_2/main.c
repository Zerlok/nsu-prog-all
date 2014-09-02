#include "mod.h"

int main() {
	int a, b;
	
	scanf("%d %d", &a, &b);
	printf("------\n");
	if (b) {
		printf("%d\n", get_gcd(a, b));
	} else {
		printf("Zero Division.\n");
	}
	return 0;
}
