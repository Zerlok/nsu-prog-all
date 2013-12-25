#include <stdio.h>
#include <string.h>

struct Tree {
	int value;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *stree(struct Tree *root, struct Tree *new_root, int val);

struct Tree *insert(struct Tree *root, int val);

void print_help();

void print_tree(struct Tree *root);
