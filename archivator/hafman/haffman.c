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
		zipped_file->new_size = 0;
		zipped_file->old_size = 0;
	}
	else
	{
		zipped_file->root = get_bintree(symbols_list);
		zipped_file->list = symbols_list;
		zipped_file->new_size = 0;
		zipped_file->old_size = file_size;
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
	unsigned long int print_num = 0, max_prints = zipped_file->old_size;

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
