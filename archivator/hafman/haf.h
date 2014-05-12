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
int get_hash(unsigned char symbol);
void print_list(BINTREE *list);
int append_list(BINTREE *list, int hash, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);
BINTREE *pop_list(BINTREE **list);
BINTREE *get_symbols_list(unsigned char *string);
char *get_encoded(BINTREE *list, unsigned char symbol);

/* BINTREE */
int print_bintree(BINTREE *root, char *seq);
int count_bintree_codes(BINTREE *root, char *seq);
BINTREE *get_bintree(BINTREE *list);

/* MAIN FUNCTIONS */
char *encode(char *string);
// char *decode(BINTREE *root, char *string);
int decode(BINTREE *root, char *string);