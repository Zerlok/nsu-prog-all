#include "haf.h"


ARCHIVEDFILE *encode_file(FILE *file)
/*
This function uses Haffman algorithm and builds symbols frequency table and binary tree of file.

Input:
	FILE *file - the FILE pointer.

Output:
	ARCHIVEDFILE * - the pointer to ARCHIVEDFILE structure.
*/
{
	ARCHIVEDFILE *zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));

	BINTREE *symbols_list = NULL;
	unsigned long int file_size = 0;
	unsigned char chr;

	/* Append frequency table */
	while (fread(&chr, sizeof(chr), 1, file))
	{
		append_list(&symbols_list, chr);
		file_size++;
	}

	/* If file is empty */
	if (file_size == 0)
	{
		zipped_file->root = NULL;
		zipped_file->list = NULL;
		zipped_file->zipped_size = 0;
		zipped_file->original_size = 0;
	}
	else
	{
		zipped_file->root = get_bintree(symbols_list);
		zipped_file->list = symbols_list;
		zipped_file->zipped_size = 0;
		zipped_file->original_size = file_size;
	}

	return zipped_file;
}


int decode_file(FILE *file, FILE *archive_file, ARCHIVEDFILE *zipped_file)
/*
This function creates unzipped file.

Input:
	FILE *file - the FILE pointer (where to unzip).
	FILE *archive_file - the FILE pointer (archive with zipped file).
	ARCHIVEDFILE *zipped_file - the pointer to ARCHIVEDFILE structure.

Output:

*/
{
	if (zipped_file == NULL)
	{
		return 1;
	}

	BINTREE *head = zipped_file->root;
	char *buffer, chr;
	int i;
	unsigned long int print_num = 0, max_prints = zipped_file->original_size;

	/* Get to zipped file text */
	fseek(archive_file, zipped_file->start_byte, SEEK_SET);

	/* Unzip & print to file */
	while (print_num < max_prints)
	{
		/* Read zipped char */
		fread(&chr, 1, sizeof(char), archive_file);
		buffer = get_binary_code(chr); // Buffer length == 8

		i = 0;
		while (print_num < max_prints && i < 8)
		{
			/* If end head reached */
			if (head->left == NULL && head->right == NULL)
			{
				fprintf(file, "%c", (signed)head->value);
				print_num += 1;
				head = zipped_file->root;
			}
			else
			/* Go down through tree */
			{
				if (buffer[i] == '1')
				{
					head = head->left;
				}
				else
				{
					head = head->right;
				}

				i++;
			}
		}
	}

	return 0;
}


char get_as_one_char(char *string)
/*
Encodes first 8 char symbols of string to one char.

Input:
	char *string - the sequence of '0' & '1'.

Output:
	char - one char.
*/
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
/*
Decodes one char to binary code.

Input:
	char chr - one char.

Output:
	char * - the pointer to string[8] with '0' & '1'.
*/
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
/*
Makes binary tree using Haffman algorithm.

Input:
	BINTREE *main_lst - the pointer to symbols' frequency table.

Output:
	BINTREE * - the pointer to root of BINTREE.
*/
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
		
		/* Insert new vertex */
		insert_to_list(&header, new_lst);

		// print_list(main_lst);
	}
	/* The last vertex has no code" */
	new_lst->code = "";
	insert_to_list(&main_lst, new_lst); // Am I need this?

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
		left_seq = (char*)calloc(strlen(seq), sizeof(char));
		strcpy(left_seq, seq);
		strcat(left_seq, root->code);

		right_seq = (char*)calloc(strlen(seq), sizeof(char));
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
	/* If it starts with "" */
	{
		left_seq = (char*)malloc(sizeof(seq));
		strcpy(left_seq, root->code);

		right_seq = (char*)malloc(sizeof(seq));
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

	/* Check the first item */
	if (value == left_lst->value)
	{
		/* Increase count */
		left_lst->count += 1;

		/* Change main_lst pointer */
		*main_lst = left_lst->next;

		/* Insert item to list */
		insert_to_list(main_lst, left_lst);

		return 0;
	}

	right_lst = left_lst->next;

	while (right_lst != NULL)
	{
		/* If this value exists in main_lst */
		if (value == right_lst->value)
		{
			/* Increase count */
			right_lst->count += 1;

			/* Break nodes with this item */
			left_lst->next = right_lst->next;

			/* Insert item to list */
			insert_to_list(main_lst, right_lst);

			return 0;
		}
		#ifdef DEBUG
			/* Show same hash but not same values */
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
