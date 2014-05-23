#include "haf.h"


ARCHIVEDFILE *encode_file(FILE *file)
{
	ARCHIVEDFILE *zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));

	BINTREE *bin_tree, *symbols_list = NULL;
	unsigned long int file_size = 0;
	unsigned char chr;

	/* Haffman encode preparation */
	while (fread(&chr, sizeof(chr), 1, file))
	{
		append_list(&symbols_list, chr);
		file_size++;
	}

	bin_tree = get_bintree(symbols_list);

//	#ifdef DEBUG
//		print_list(symbols_list);
		print_bintree(bin_tree, "");
//	#endif

	/* If file is empty */
	if (file_size == 0)
	{
		zipped_file->root = NULL;
		zipped_file->list = NULL;
		zipped_file->new_size = 0;
		zipped_file->old_size = 0;
	}
	else
	{
		zipped_file->root = bin_tree;
		zipped_file->list = symbols_list;
		zipped_file->new_size = 0;
		zipped_file->old_size = file_size;
	}

	return zipped_file;
}


int decode_file(FILE *file, FILE *archive_file, ARCHIVEDFILE *zipped_file)
{
	if (zipped_file == NULL)
	{
		return 1;
	}

	BINTREE *head = zipped_file->root;
	char *buffer, chr;
	int j;
	unsigned long int prnt = 0, i = 0, max_len = zipped_file->new_size, max_prints = zipped_file->old_size;

	fseek(archive_file, zipped_file->start_byte, SEEK_SET);
	while (prnt < max_prints && i < max_len)
	{
		fread(&chr, 1, sizeof(char), archive_file);
		buffer = get_binary_code(chr);

		j = 0;
		while (prnt < max_prints && j < 8)
		{
			if (head->left == NULL && head->right == NULL)
			{
				fprintf(file, "%c", (signed)head->value);
				prnt += 1;
				head = zipped_file->root;
			}
			else
			{
				if (buffer[j] == '1')
				{
					head = head->left;
				}
				else
				{
					head = head->right;
				}

				j++;
			}
		}

		i++;
	}

	return 0;
}


char get_as_one_char(char *string)
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


BINTREE *get_bintree(BINTREE *main_lst)
{
	BINTREE *new_lst, *left_lst, *right_lst, *header = main_lst;

	/* If it's no symbols in file */
	if (header == NULL)
	{
		return NULL;
	}

	/* If it's only one symbol in file */
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
/*
Counts paths to every head end (symbol).

Input:
	BINTREE *root - the pointer to binary tree structure.
	char *seq - the pointer to the path sequence.
	unsigned long int - the depth of vertex.
*/
{
	char *left_seq = NULL, *right_seq = NULL;

	if (root == NULL)
	{
		return len;
	}

	/* If it is the end of head */
	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		root->encoded = (char*)calloc(strlen(seq), sizeof(char));
		root->length = 0;
		strcpy(root->encoded, seq);
		strcat(root->encoded, root->code);

		return len + 2;
	}
	
	/* Append left and right sequences */
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

	/* Go down through tree */
	len = count_bintree_codes(root->left, left_seq, len);
	len = count_bintree_codes(root->right, right_seq, len);

	root->length = len;

	return len;
}


int write_bintree_to_file(FILE *file, BINTREE *root)
/*
Writes the tree into file.

Input:
	FILE *file - the pointer to the file.
	BINTREE *root - the pointer to the binary tree.
*/
{
	if (root == NULL)
	{
		return 1;
	}

	/* If it is the end of head */
	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		fprintf(file, "S%c", (char)root->value);
		return 0;
	}

	/* V for Vertex */
	fprintf(file, "V");

	/* Go down through tree */
	write_bintree_to_file(file, root->left);
	write_bintree_to_file(file, root->right);

	return 0;
}


unsigned long int build_bintree_from_file(FILE *file, BINTREE *root, unsigned long int length, char *code)
/*
Reads the tree from file.

Input:
	FILE *file - the pointer to the file.
	BINTREE *root - the pointer to the binary tree structure.
	unsigned long int length - the length of written tree symbols in file.
	char *code - the pointer to trunk code ("1" or "0").

Output:
	unsigned long int - the depth of this root.
*/
{
	char chr;

	if (length > 0)
	{
		root->code = code;

		fread(&chr, 1, sizeof(char), file);
		/* Create the head end if the symbol */
		if (chr == 'S')
		{
			fread(&chr, 1, sizeof(char), file);
			root->next = root->left = root->right = NULL;
			root->hash = get_hash((unsigned)chr);
			root->count = root->length = 0;
			root->value = (unsigned)chr;

			return length - 2;
		}

		/* Hash is zero for all vertices */
		root->hash = 0;
		length -= 1;

		/* Left trunk */
		root->left = (BINTREE*)malloc(sizeof(BINTREE));
		length = build_bintree_from_file(file, root->left, length, "1");

		/* Right trunk */
		root->right = (BINTREE*)malloc(sizeof(BINTREE));
		length = build_bintree_from_file(file, root->right, length, "0");
	}

	return length;
}


int print_bintree(BINTREE *root, char *seq)
/*
Prints the binary tree on screen.

Input:
	BINTREE *root - the pointer to the binary tree structure.
	char *seq - the sequence of codes (path to the value).
*/
{
	char *left_seq = NULL, *right_seq = NULL;

	if (root == NULL)
	{
		return 1;
	}

	/* If it is the end of head */
	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("%c == '%s%s'\n", (signed)root->value, seq, root->code);

		return 0;
	}

	/* Append left and right sequences */
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

	/* Go down through tree */
	print_bintree(root->left, left_seq);
	print_bintree(root->right, right_seq);

	return 0;
}

unsigned int get_hash(unsigned char symbol)
/*
Creates the integer value from symbol.

Input:
	unsigned char symbol - the symbol.

Output:
	unsigned int - the hash value.
*/
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


BINTREE *pop_list(BINTREE **main_lst)
/*
Pops the first list item from binary tree structure.

Input:
	BINTREE **main_lst - the address of pointer to binary tree list structure.

Output:
	BINTREE * - the pointer to the first item.
*/
{
	BINTREE *lst = (*main_lst);
	
	/* Shift the pointer if not NULL */
	if ((*main_lst) != NULL)
	{
		*main_lst = (*main_lst)->next;
	}

	return lst;
}


int append_list(BINTREE **main_lst, unsigned char value)
/*
Appends the list of symbols with new item or increments the existed symbol's counter.

Input:
	BINTREE **main_lst - the address of pointer to binary tree list structure.
	unsigned char value - the symbol.
*/
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

	if (value == left_lst->value)
	{
		left_lst->count += 1;
		*main_lst = left_lst->next;
		insert_to_list(main_lst, left_lst);

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
		}
		#ifdef DEBUG
			else if (hash == right_lst->hash && value != right_lst->value)
			{
				printf("Hash collision:\n%d for (%c) and (%c) values!!!\n", hash, value, right_lst->value);
			}
		#endif

		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	/* Insert a new item */
	insert_to_list(main_lst, new_lst);

	return 0;
}


int insert_to_list(BINTREE **main_lst, BINTREE *new_lst)
/*
Inserts the new item to the list.

Input:
	BINTREE **main_lst - the address of pointer to binary tree list structure.
	BINTREE *new_lst - the pointer to the new item.
*/
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


char *get_encoded(BINTREE *main_lst, unsigned char symbol)
/*
Returns the encoded symbol.

Input:
	BINTREE *main_lst - the pointer to binary tree list structure.
	unsigned char - the symbol.

Output:
	char * - the pointer to binary code of this symbol.
*/
{
	BINTREE *lst = main_lst;

	while (lst != NULL)
	{
		/* If not the vertex and values are same */
		if (lst->hash != 0 && lst->value == symbol)
		{
			return lst->encoded;
		}

		lst = lst->next;
	}

	return NULL;
}


void print_list(BINTREE *main_lst)
/*
Prints the list of symbols.

Input:
	BINTREE *main_lst - the pointer to hte list.
*/
{
	BINTREE *lst = main_lst;

	printf("[\n");
	while (lst != NULL)
	{
		/* If it's not the vertex (the end of head in tree) */
		if (lst->hash != 0)
		{
			printf("%05d : %x (%ld) enc (%s)\n", lst->hash, lst->value, lst->count, lst->encoded);
		}
		/* If it's the vertex */
		else
		{
			printf("{0 : %x (%ld)}\n", lst->value, lst->count);
		}

		lst = lst->next;
	}
	printf("]\n");
}
