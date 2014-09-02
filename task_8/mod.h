#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree {
	int value;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *insert(struct Tree *root, int val);

void print_help();

void print_tree(struct Tree *root);
