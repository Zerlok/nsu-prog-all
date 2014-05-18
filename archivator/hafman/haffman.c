#include "haf.h"

//#include "../debug.h"
#define DEBUG_

#ifdef DEBUG
	#define PRINT_RUN \
		print_start_func(__func__);
	#define PRINT_END \
		print_end_func(__func__);
#else
	#define PRINT_RUN
	#define PRINT_END
#endif


ARCHIVEDFILE *encode_file(FILE *file)
{
	PRINT_RUN

	ARCHIVEDFILE *zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));
	BINTREE *bin_tree, *symbols_list = NULL;
	unsigned long int new_size, file_size = 0;
	unsigned char chr;
	char *new_string;

	/* Haffman encode preparation */
	while (fread(&chr, sizeof(chr), 1, file))
	{
//		printf("'%c'\n", chr);
		if (chr != (unsigned)"")
		{
			append_list(&symbols_list, chr);
			file_size++;
		}
	}
	new_size = file_size;

	/* If file is empty */
	if (file_size == 0)
	{
		zipped_file->text = "";
		zipped_file->root = NULL;
		zipped_file->new_size = 0;
		zipped_file->old_size = 0;

		return zipped_file;
	}

	bin_tree = get_bintree(symbols_list);
	print_list(symbols_list);
	print_bintree(bin_tree, "");
	write_bintree(bin_tree, 0);

	/* Encoding */
	fseek(file, 0, SEEK_SET);
	new_string = (char*)calloc(new_size * 2, sizeof(char));

	while (fread(&chr, sizeof(chr), 1, file))
	{
		if (chr != (unsigned)"")
		{
			printf("'%c' (%d)\n", chr, (int)chr);

			if (2 * strlen(new_string) > new_size)
			{
				new_string = (char*)realloc(new_string, new_size * 2);
				new_size *= 2;
			}
			strcat(new_string, get_encoded(symbols_list, chr));
		}
	}

	/* Zipped file structure creation */
	zipped_file->text = get_letters(new_string);
	zipped_file->root = bin_tree;
	zipped_file->new_size = strlen(zipped_file->text);
	zipped_file->old_size = file_size;

	/* Decode test */
	decode_string(bin_tree, new_string);

	return zipped_file;
}


char *get_letters(char *string)
{
	unsigned int i = 0;
//	char *new_string = (char*)malloc(sizeof(string));
	char *new_string = (char*)calloc((int)(strlen(string) / 8), sizeof(char));
	char little_string[8];

//	printf("All file code is:\n'");
	while (i < strlen(string))
	{
		if (i > 0 && (i % 8) == 0)
		{
			printf("'%s' == '%c'\n", little_string, get_as_one_char(little_string));
			new_string[(int)(i / 8) - 1] = (char)(get_as_one_char(little_string));
		}
		little_string[i % 8] = string[i];
//		printf("%c", string[i]);
		i++;
	}
	i--;
//	printf("'\n");

	if ((i % 8) != 0)
	{
		while ((i % 8) != 0)
		{
			little_string[i % 8] = '0';
			i++;
		}
		printf("'%s' == '%c'\n", little_string, get_as_one_char(little_string));
		new_string[(int)(i / 8) - 1] = (char)(get_as_one_char(little_string));
	}
	return new_string;
}


char get_as_one_char(char string[8])
{
	int i, chr = 0;
	int mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	for (i = 0; i < 8; i++)
	{
		if (string[i] == '1')
		{
			chr += mask[i];
		}
	}

	return (char)chr;
}


char *encode_string(char *string)
{
	char *new_string = (char*)malloc(sizeof(string));
	unsigned long int i;

	BINTREE *symbols_list = get_symbols_list((unsigned char*)string);
	#ifdef DEBUG
		print_list(symbols_list);
	#endif
	
	BINTREE *bin_tree = get_bintree(symbols_list);;
	#ifdef DEBUG
		print_bintree(bin_tree, "");
	#endif

	for (i = 0; i < strlen(string); i++)
	{
		new_string = strcat(new_string, get_encoded(symbols_list, string[i]));
	}

//	#ifdef DEBUG
//		printf("decode is: '%s'\n", decode(bin_tree, new));
//		decode(bin_tree, new);
//	#endif

	return get_letters(new_string);
}


int decode_string(BINTREE *root, char *string)
{
	unsigned long int i;
	// char *new = (char*)malloc(sizeof(string));
	BINTREE *head = root;

	if (root == NULL)
	{
		return 1;
	}

	// strcpy(new, "");
	printf("\nDecode is:\n");

	for (i = 0; i < strlen(string); i++)
	{
		/* If vertex is last in this trunk, print it */
		if ((head->left == NULL) && (head->right == NULL))
		{
			printf("%c", (signed)head->value);
			head = root;
		}

		/* If not: go down through tree */
		if (string[i] == '1')
		{
			head = head->left;
		}
		else if (string[i] == '0')
		{
			head = head->right;
		}
		else
		{
			printf("Another code (%c) was found at %s\n", string[i], __func__);
			exit(1);
		}
	}
	
	/* Last symbol */
	if (root->left != NULL && root->right != NULL)
	{
		printf("%c", (signed)head->value);
	}

	printf("\n");
	return 0;
}


char *get_encoded(BINTREE *main_lst, unsigned char symbol)
{
	BINTREE *lst = main_lst;

	while (lst != NULL)
	{
		if (lst->hash != 0 && lst->value == symbol)
		{
			return lst->encoded;
		}

		lst = lst->next;
	}

	return NULL;
}


BINTREE *get_bintree(BINTREE *main_lst)
{
	BINTREE *new_lst, *left_lst, *right_lst, *header = main_lst;

	/* If only one letter in code */
	if (header->next == NULL)
	{
		header->left = header->right = NULL;
		header->code = "0";
		return header;
	}

	/* Otherwise */
	while ((left_lst = pop_list(&header)) != NULL
		&& (right_lst = pop_list(&header)) != NULL)
	{
		/* Codes assigning */
		left_lst->code = "1";
		right_lst->code = "0";

		/* New vertex creation */
		new_lst = (BINTREE*)malloc(sizeof(BINTREE));
		new_lst->left = left_lst;
		new_lst->right = right_lst;
		new_lst->hash = 0;
		new_lst->value = 0;
		new_lst->count = left_lst->count + right_lst->count;
		
		// print_list(main_lst);
		// print_list(new_lst);
		
		/* Insert new vertex */
		insert_to_list(&header, new_lst);

		// print_list(main_lst);
	}
	/* The last vertex has no code" */
	new_lst->code = "";
	insert_to_list(&main_lst, new_lst);

	/* All values assigning */
	count_bintree_codes(new_lst, "");

	return new_lst;
}


int count_bintree_codes(BINTREE *root, char *seq)
{
	char *left_seq = NULL, *right_seq = NULL;

	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		root->encoded = (char*)calloc(strlen(seq) + 1, sizeof(char));
		strcpy(root->encoded, seq);
		strcat(root->encoded, root->code);

		return 0;
	}
	
	if (strlen(seq) != 0)
	{
		left_seq = (char*)calloc(strlen(seq) + 1, sizeof(char));
		strcpy(left_seq, seq);
		strcat(left_seq, root->code);

		right_seq = (char*)calloc(strlen(seq) + 1, sizeof(char));
		strcpy(right_seq, seq);
		strcat(right_seq, root->code);
	}
	else
	{
		/* If it starts with "" */
		left_seq = (char*)malloc(sizeof(seq));
		right_seq = (char*)malloc(sizeof(seq));
		strcpy(left_seq, root->code);
		strcpy(right_seq, root->code);
	}
	
	count_bintree_codes(root->left, left_seq);
	count_bintree_codes(root->right, right_seq);

	return 0;
}


int write_bintree(BINTREE *root, int lvl)
{
	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("(%c)[%d]\n", (char)root->value, lvl);
		return 0;
	}

	printf("N");

	write_bintree(root->left, lvl + 1);
	write_bintree(root->right, lvl + 1);

	return 0;
}


int print_bintree(BINTREE *root, char *seq)
{
	char *left_seq = NULL, *right_seq = NULL;

	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("%c == '%s%s'\n", (signed)root->value, seq, root->code);

		return 0;
	}

	if (strlen(seq) != 0)
	{
		left_seq = (char*)calloc(strlen(seq) + 1, sizeof(char));
		strcpy(left_seq, seq);
		strcat(left_seq, root->code);

		right_seq = (char*)calloc(strlen(seq) + 1, sizeof(char));
		strcpy(right_seq, seq);
		strcat(right_seq, root->code);
	}
	else
	{
		/* If it starts with "" */
		left_seq = (char*)malloc(sizeof(seq));
		right_seq = (char*)malloc(sizeof(seq));
		strcpy(left_seq, root->code);
		strcpy(right_seq, root->code);
	}

	print_bintree(root->left, left_seq);
	print_bintree(root->right, right_seq);
	return 0;
}

 
int get_hash(unsigned char symbol)
{
	int hash;

	if (!symbol)
	{
		return (int)symbol + 9;
	}

	hash = (
		abs(((int)symbol * 'A')
		 + abs((symbol - 'a') * (symbol - 'z'))
	 	 - 'Z'
	 	)) % 10000;

	if ((int)(hash / 10000) == 0)
	{
		hash += 1000 * ((int)symbol % 10);
	}

	return hash;
}

BINTREE *get_symbols_list(unsigned char *string)
{
	BINTREE *symbols_list = (BINTREE*)malloc(sizeof(BINTREE));
	unsigned long int i;
	
	for (i = 0; i < strlen((char*)string); i++)
	{
		append_list(&symbols_list, string[i]);
	}
	
	return symbols_list->next;
}


BINTREE *pop_list(BINTREE **main_lst)
{
	BINTREE *lst = (*main_lst);
	
	if ((*main_lst) != NULL)
	{
		*main_lst = (*main_lst)->next;
	}

	return lst;
}


int append_list(BINTREE **main_lst, unsigned char value)
{
	int hash = get_hash(value);
	BINTREE *left_lst = (*main_lst), *right_lst;
	BINTREE *new_lst = (BINTREE*)malloc(sizeof(BINTREE));

	new_lst->left = new_lst->right = new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->count = 1;
	new_lst->code = "0";
	new_lst->value = value;

	if (left_lst == NULL)
	{
		*main_lst = new_lst;

		return 0;
	}

	right_lst = left_lst->next;

	while (right_lst != NULL)
	{
		if (value == right_lst->value)
		{
			right_lst->count += 1;
			left_lst->next = right_lst->next;	
			insert_to_list(main_lst, right_lst);

			return 0;
		}

		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	insert_to_list(main_lst, new_lst);

	return 0;
}


int insert_to_list(BINTREE **main_lst, BINTREE *new_lst)
{
	BINTREE *left_lst = (*main_lst), *right_lst;

	if (left_lst == NULL)
	{
		*main_lst = new_lst;
		
		return 0;
	}
	right_lst = (*main_lst)->next;

	while ((right_lst != NULL)
		&& (new_lst->count > right_lst->count))
	{
		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	left_lst->next = new_lst;
	new_lst->next = right_lst;
	
	return 0;
}


void print_list(BINTREE *main_lst)
{
	BINTREE *lst = main_lst;

	printf("[\n");
	while (lst != NULL)
	{
		if (lst->hash == 1)
		{
			printf("[1 : %x (%ld)]\n", lst->value, lst->count);
		}
		else
		{
			printf("%05d : %x (%ld)\n", lst->hash, lst->value, lst->count);
		}

		lst = lst->next;
	}
	printf("]\n");
}
