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
	unsigned long int file_size = 0;
	unsigned char chr;
	char *new_string;

	/* Haffman encode preparation */
	while (fread(&chr, sizeof(chr), 1, file))
	{
		append_list(&symbols_list, chr);
		file_size++;
	}
//	print_list(symbols_list);
	bin_tree = get_bintree(symbols_list);

	/* Encoding */
	fseek(file, 0, SEEK_SET);
	new_string = (char*)malloc(sizeof(char));

	while (fread(&chr, sizeof(chr), 1, file))
	{
		new_string = strcat(new_string, get_encoded(symbols_list, chr));
	}

	/* Zipped file structure creation */
	zipped_file->text = get_letters(new_string);
	zipped_file->root = bin_tree;
	zipped_file->new_size = strlen(zipped_file->text);
	zipped_file->old_size = file_size;

	return zipped_file;
}


char *get_letters(char *string)
{
	unsigned int i = 0;
//	char *new_string = (char*)malloc(sizeof(string));
	char *new_string = (char*)calloc((int)(strlen(string) / 8), sizeof(char));
	char little_string[8];

	while (i < strlen(string))
	{
		if (i > 0 && (i % 8) == 0)
		{
			new_string[(int)(i / 8) - 1] = (char)(get_as_one_char(little_string));
		}
		little_string[i % 8] = string[i];
		i++;
	}

	if ((i % 8) != 0)
	{
		while ((i % 8) != 0)
		{
			little_string[i % 8] = '0';
			i++;
		}
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
	printf("Decode is: ");

	for (i = 0; i < strlen(string); i++)
	{
		if ((head->left == NULL) && (head->right == NULL))
		{
			// strcat(new, (char)head->value);
			printf("%c", (signed)head->value);
			head = root;
		}
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
			exit(1);
		}
	}
	
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
		if (lst->value == symbol)
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
		new_lst->hash = 1;
		new_lst->value = (unsigned)"";
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
	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		root->encoded = (char*)malloc(sizeof(seq));
		strcpy(root->encoded, seq);
		strcat(root->encoded, root->code);

		return 0;
	}
	
	char *left_seq = (char*)malloc(sizeof(seq));
	char *right_seq = (char*)malloc(sizeof(seq));

	if (strlen(seq) != 0)
	{
		left_seq = right_seq = strcat(seq, root->code);
	}
	else
	{
		/* If it starts with "" */
		strcpy(left_seq, root->code);
		strcpy(right_seq, root->code);
	}
	
	count_bintree_codes(root->left, left_seq);
	count_bintree_codes(root->right, right_seq);

	return 0;
}


int print_bintree(BINTREE *root, char *seq)
{
	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("%c == %s%s\n", (signed)root->value, seq, root->code);

		return 0;
	}
	
	char *left_seq = (char*)malloc(sizeof(seq));
	char *right_seq = (char*)malloc(sizeof(seq));

	if (strlen(seq) != 0)
	{
		left_seq = right_seq = strcat(seq, root->code);
	}
	else
	{
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
		return (int)symbol + 1;
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
			printf("[1 : %x (%d)]\n", lst->value, lst->count);
		}
		else
		{
			printf("%05d : %x (%d)\n", lst->hash, lst->value, lst->count);
		}

		lst = lst->next;
	}
	printf("]\n");
}
