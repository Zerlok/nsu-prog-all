#include "haf.h"


ARCHIVEDFILE *encode_file(FILE *file)
{
	ARCHIVEDFILE *zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));
	zipped_file->name = (char*)calloc(1, sizeof(char));

	BINTREE *bin_tree, *symbols_list = NULL;
	unsigned long int new_size, file_size = 0;
	unsigned char chr;
	char *new_string;

	/* Haffman encode preparation */
	while (fread(&chr, sizeof(chr), 1, file))
	{
		append_list(&symbols_list, chr);
		file_size++;
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
//	print_list(symbols_list);
//	print_bintree(bin_tree, "");

	/* Encoding */
	fseek(file, 0, SEEK_SET);
	new_string = (char*)calloc(new_size * 2, sizeof(char));

	while (fread(&chr, sizeof(chr), 1, file))
	{
		if (2 * strlen(new_string) > new_size)
		{
			new_string = (char*)realloc(new_string, new_size * 2);
			new_size *= 2;
		}
		strcat(new_string, get_encoded(symbols_list, chr));
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


int decode_file(FILE *file, ARCHIVEDFILE *zipped_file)
{

	if (zipped_file->root == NULL)
	{
		return 1;
	}

	BINTREE *root = zipped_file->root;
	char *bin_code, *text = zipped_file->text;
	int j;
	unsigned long int prnt = 0, i = 0, max_len = zipped_file->new_size, max_prints = zipped_file->old_size;

	while (prnt < max_prints && i < max_len)
	{
		bin_code = get_binary_code(text[i]);

		j = 0;
		while (prnt < max_prints && j < 8)
		{
			if (root->left == NULL && root->right == NULL)
			{
				fprintf(file, "%c", (signed)root->value);
				prnt += 1;
				root = zipped_file->root;
			}
			else
			{
				if (bin_code[j] == '1')
				{
					root = root->left;
				}
				else
				{
					root = root->right;
				}

				j++;
			}
		}

		i++;
	}

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


char *get_letters(char *string)
{
	unsigned int i = 0;
	char *new_string = (char*)calloc((int)(strlen(string) / 8), sizeof(char));
	char little_string[8];

	while (i < strlen(string))
	{
		if (i > 0 && (i % 8) == 0)
		{
			new_string[(int)(i / 8) - 1] = get_as_one_char(little_string);
		}
		little_string[i % 8] = string[i];

		i++;
	}

	i--;
	if ((i % 8) != 0)
	{
		while ((i % 8) != 0)
		{
			little_string[i % 8] = '0';
			i++;
		}
		new_string[(int)(i / 8) - 1] = get_as_one_char(little_string);
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


char *get_binary_code(unsigned char chr)
{
	char *bin_code = (char*)calloc(8, sizeof(char));
	unsigned int code = chr, i = 0, sum = 0, mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	while (i < 8)
	{
		if (sum + mask[i] <= code)
		{
			bin_code[i] = '1';
			sum += mask[i];
		}
		else
		{
			bin_code[i] = '0';
		}

		i++;
	}

	return bin_code;
}


int decode_string(BINTREE *root, char *string)
{
	unsigned long int i;
	BINTREE *head = root;

	if (root == NULL)
	{
		return 1;
	}

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


BINTREE *get_bintree(BINTREE *main_lst)
{
	BINTREE *new_lst, *left_lst, *right_lst, *header = main_lst;

	/* If only one letter in code */
	if (header->next == NULL)
	{
		header->left = header->right = NULL;
		header->code = "1";
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
	count_bintree_codes(new_lst, "", 0);

	return new_lst;
}


unsigned long int count_bintree_codes(BINTREE *root, char *seq, unsigned long int len)
{
	char *left_seq = NULL, *right_seq = NULL;

	if (root == NULL)
	{
		return len;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		root->encoded = (char*)calloc(strlen(seq) + 1, sizeof(char));
		root->length = 0;
		strcpy(root->encoded, seq);
		strcat(root->encoded, root->code);

		return len + 2;
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
	len += 1;

	len = count_bintree_codes(root->left, left_seq, len);
	len = count_bintree_codes(root->right, right_seq, len);
	root->length = len;

	return len;
}


int write_bintree_to_file(FILE *file, BINTREE *root)
{
	if (root == NULL)
	{
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		fprintf(file, "S%c", (char)root->value);
		return 0;
	}

	fprintf(file, "N");

	write_bintree_to_file(file, root->left);
	write_bintree_to_file(file, root->right);

	return 0;
}


unsigned long int build_bintree_from_file(FILE *file, BINTREE *root, unsigned long int length, char *code)
{
	char chr;

	if (length > 0)
	{
		root->code = code;

		fread(&chr, 1, 1, file);
		if (chr == 'S')
		{
			fread(&chr, 1, 1, file);
			root->next = root->left = root->right = NULL;
			root->hash = get_hash((unsigned)chr);
			root->count = root->length = 0;
			root->value = (unsigned)chr;

			return length - 2;
		}

		length -= 1;

		root->hash = 0;
		root->left = (BINTREE*)malloc(sizeof(BINTREE));
		root->right = (BINTREE*)malloc(sizeof(BINTREE));
		length = build_bintree_from_file(file, root->left, length, "1");
		length = build_bintree_from_file(file, root->right, length, "0");
	}

	return length;
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

unsigned int get_hash(unsigned char symbol)
{
	unsigned int hash;

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
	unsigned int hash = get_hash(value);
	BINTREE *left_lst = (*main_lst), *right_lst;

	/* New list item */
	BINTREE *new_lst = (BINTREE*)malloc(sizeof(BINTREE));
	new_lst->left = new_lst->right = new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->count = 1;
	new_lst->code = 0;
	new_lst->value = value;

	/* if main_lst is empty */
	if (left_lst == NULL)
	{
		*main_lst = new_lst;

		return 0;
	}
	right_lst = left_lst->next;

	while (right_lst != NULL)
	{
		/* If this value exists in main_lst */
		if (value == right_lst->value)
		{
			right_lst->count += 1;
			left_lst->next = right_lst->next;	
			insert_to_list(main_lst, right_lst);

			return 0;
		} else if (hash == right_lst->hash && value != right_lst->value)
		{
			printf("Hash collision:\n%d for (%c) and (%c) values!!!\n", hash, value, right_lst->value);
		}

		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	/* Insert a new item */
	insert_to_list(main_lst, new_lst);

	return 0;
}


int insert_to_list(BINTREE **main_lst, BINTREE *new_lst)
{
	BINTREE *left_lst = (*main_lst), *right_lst;

	/* If main_lst is empty */
	if (left_lst == NULL)
	{
		*main_lst = new_lst;
		
		return 0;
	}
	right_lst = (*main_lst)->next;

	/* Find grater count item */
	while ((right_lst != NULL)
		&& (new_lst->count > right_lst->count))
	{
		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	/* Insert */
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
		if (lst->hash != 0)
		{
			printf("%05d : %x (%ld)\n", lst->hash, lst->value, lst->count);
		}
		else
		{
			printf("{0 : %x (%ld)}\n", lst->value, lst->count);
		}

		lst = lst->next;
	}
	printf("]\n");
}
