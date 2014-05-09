#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	int hash;
	int count;
	char *code;
	unsigned char value;
} BINTREE;


void print_list(BINTREE *list);
int get_hash(unsigned char symbol);
// int shift_list(BINTREE **list, BINTREE *new_lst);
// int insert(BINTREE **list, int hash, unsigned char value);
int insert(BINTREE **list, BINTREE *new_lst);
int append(BINTREE *list, int hash, unsigned char value);
BINTREE *exclude(BINTREE *list, int num);
char *encode(char *string);
BINTREE *get_symbols_list(unsigned char *string);
BINTREE *pop(BINTREE **list);

int print_bintree(BINTREE *root, char *seq);
// BINTREE *get_trunk(char *code, unsigned char value);
BINTREE *get_trunk(char *code, BINTREE *list);
BINTREE *build_bintree(BINTREE *list);
// int search_symbol(BINTREE *root, char *seq);
