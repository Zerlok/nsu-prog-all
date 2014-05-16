#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BinaryTree
{
	struct BinaryTree *left, *right, *next;
	unsigned int hash;
	unsigned long int count;
	char *code, *encoded;
	unsigned char value;
} BINTREE;


typedef struct ArchivedFile
{
//    struct ArchivedFile *next;
	BINTREE *root;
	int old_size, new_size;
	char *text;

} ARCHIVEDFILE;


/* LIST */
int get_hash(unsigned char symbol);
void print_list(BINTREE *list);
int append_list(BINTREE **list, unsigned char value);
int insert_to_list(BINTREE **list, BINTREE *new_lst);
BINTREE *pop_list(BINTREE **list);
BINTREE *get_symbols_list(unsigned char *string);
char *get_encoded(BINTREE *list, unsigned char symbol);

/* BINTREE */
int write_bintree(BINTREE *root, int lvl);
int print_bintree(BINTREE *root, char *seq);
int count_bintree_codes(BINTREE *root, char *seq);
BINTREE *get_bintree(BINTREE *list);

/* MAIN FUNCTIONS */
char *encode_string(char *string);
int decode_string(BINTREE *root, char *string);

char *get_letters(char *string);
char get_as_one_char(char string[8]);

ARCHIVEDFILE *encode_file(FILE *file);
char *decode_file(FILE *file);
