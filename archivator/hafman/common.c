#include "haf.h"


/* ----- BINARY NUMS ----- */

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


/* ----- BINARY TREE ----- */

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


/* ---- LIST ---- */

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
