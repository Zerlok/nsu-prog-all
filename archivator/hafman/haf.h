#ifndef __HAF_H__
#define __HAF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* ---- BINARY TREE STRUCTURE ----- */
typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	unsigned int hash;
	unsigned char value;
	char *code, *encoded;
	unsigned long int count, length;
} BINTREE;


/* ----- ZIPPED FILE STRUCTURE ----- */
typedef struct ArchivedFile
{
	BINTREE *root, *list;
	long int start_byte;
	char *name;
	unsigned long int old_size, new_size;

} ARCHIVEDFILE;


/* ----- LIST.C FUNCTIONS ----- */
BINTREE *pop_list(BINTREE **list);
int append_list(BINTREE **list, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);


/* ----- COMMON FUNCTIONS ----- */
unsigned int get_hash(unsigned char symbol);
void print_list(BINTREE *list);

char *get_encoded(BINTREE *list, unsigned char symbol);
char get_as_one_char(char *string);
char *get_binary_code(unsigned char chr);

int print_bintree(BINTREE *root, char *seq);


/* ----- BINTREE FUNCTIONS ----- */
unsigned long int count_bintree_codes(
		BINTREE *root,
		char *seq,
		unsigned long int len
);
unsigned long int build_bintree_from_file(
		FILE *file,
		BINTREE *root,
		unsigned long int length,
		char *code
);
int write_bintree_to_file(FILE *file, BINTREE *root);
BINTREE *get_bintree(BINTREE *list);


/* ----- MAIN FUNCTIONS ----- */
ARCHIVEDFILE *encode_file(FILE *file);
int decode_file(FILE *file, FILE *archive_file, ARCHIVEDFILE *zipped_file);

#endif
