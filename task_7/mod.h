#include <stdio.h>
#include <stdlib.h>

struct List
{
	struct List * next;
	int value;
};

struct List *init_list();

void print_list(struct List * list);

int insert(struct List ** list, int value);
