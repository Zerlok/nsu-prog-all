#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	int hash;
	int count;
	char *code, *encoded;
	unsigned char value;
} BINTREE;


/* LIST */
void print_list(BINTREE *list);
int get_hash(unsigned char symbol);
int append(BINTREE *list, int hash, unsigned char value);
int insert(BINTREE **list, BINTREE *new_lst);
BINTREE *pop(BINTREE **list);
BINTREE *get_symbols_list(unsigned char *string);

/* BINTREE */
int print_bintree(BINTREE *root, char *seq);
int assign_bintree_values(BINTREE *root, char *seq);
BINTREE *build_bintree(BINTREE *list);

/* MAIN FUNCTIONS */
char *encode(char *string);
