#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right;
	int value;
} BINTREE;


typedef struct SymbolList
{
	struct SymbolList *next;

	int hash;
	unsigned char value;
	int count;
} SYMLIST;


void print_list(SYMLIST *list);
int get_hash(unsigned char symbol);
// int shift_list(SYMLIST **list, SYMLIST *new_lst);
// int insert(SYMLIST **list, int hash, unsigned char value);
int insert(SYMLIST *list, SYMLIST *new_lst);
int append(SYMLIST *list, int hash, unsigned char value);
char *encode(char *string);
SYMLIST *get_symbols_list(unsigned char *string);
