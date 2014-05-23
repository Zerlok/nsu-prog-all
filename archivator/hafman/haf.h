#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	unsigned int hash;
	unsigned char value;
	char *code, *encoded;
	unsigned long int count, length;
} BINTREE;


typedef struct ArchivedFile
{
	BINTREE *root, *list;
	long int start_byte;
	char *name;
	unsigned long int old_size, new_size;

} ARCHIVEDFILE;


/* LIST */
unsigned int get_hash(unsigned char symbol);
void print_list(BINTREE *list);
int append_list(BINTREE **list, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);
BINTREE *pop_list(BINTREE **list);
BINTREE *get_symbols_list(unsigned char *string);

/* CODES */
char *get_encoded(BINTREE *list, unsigned char symbol);
char *get_letters(char *string);
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

int decode_string(BINTREE *root, char *string);
