#include "mod.h"

int get_gcd(int a, int b) {
	int c;
	while (a % b) {
		c = a;
		a = b;
		b = c % b;
	}
	return b;
}
