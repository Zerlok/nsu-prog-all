#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	unsigned int hash;
	unsigned long int count, length;
	char *code, *encoded;
	unsigned char value;
} BINTREE;


typedef struct ArchivedFile
{
//    struct ArchivedFile *next;
	BINTREE *root;
	unsigned long int old_size, new_size;
	char *text, *name;

} ARCHIVEDFILE;


/* LIST */
unsigned int get_hash(unsigned char symbol);
void print_list(BINTREE *list);
int append_list(BINTREE **list, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);
BINTREE *pop_list(BINTREE **list);
BINTREE *get_symbols_list(unsigned char *string);
char *get_encoded(BINTREE *list, unsigned char symbol);

/* BINTREE */
int write_bintree(FILE *file, BINTREE *root);
int print_bintree(BINTREE *root, char *seq);
unsigned long int count_bintree_codes(BINTREE *root, char *seq, unsigned long int len);
BINTREE *get_bintree(BINTREE *list);

/* MAIN FUNCTIONS */
int decode_string(BINTREE *root, char *string);

char *get_letters(char *string);
char get_as_one_char(char string[8]);

ARCHIVEDFILE *encode_file(FILE *file);
char *decode_file(
		FILE *file,
		unsigned long int from_byte,
		unsigned long int to_byte,
		BINTREE *root
);
