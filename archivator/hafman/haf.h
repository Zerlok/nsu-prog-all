#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;			// Binary tree (left, right), list (next)
	unsigned int hash;								// Hash value
	unsigned char value;							// Value of symbol
	char *code, *encoded;							// The code of vertex in BINTREE (1 or 0), path to vertex (1010101)
	unsigned long int count, length;				// The frequency of symbol appearing in file, depth of vertex in binary tree
} BINTREE;											// Binary tree vertex


typedef struct ArchivedFile
{
	BINTREE *root, *list;							// The file's binary tree, the frequency taable of symbols in file
	long int start_byte;							// The first byte of zipped file text
	unsigned long int original_size, zipped_size;	// The unzipped size, the zipped size
	char *name;										// The name of file
} ARCHIVEDFILE;										// The zipped file structure


/* LIST */
unsigned int get_hash(unsigned char symbol);
void print_list(BINTREE *list);
int append_list(BINTREE **list, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);
BINTREE *pop_list(BINTREE **list);


/* CODES */
char *get_encoded(BINTREE *list, unsigned char symbol);
char get_as_one_char(char *string);
char *get_binary_code(unsigned char chr);


/* BINTREE */
int print_bintree(BINTREE *root, char *seq);
int write_bintree_to_file(FILE *file, BINTREE *root);
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
BINTREE *get_bintree(BINTREE *list);


/* MAIN FUNCTIONS */
ARCHIVEDFILE *encode_file(FILE *file);
int decode_file(FILE *file, FILE *archive_file, ARCHIVEDFILE *zipped_file);
