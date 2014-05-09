#include "haf.h"

#include "../debug_trar.h"
#define DEBUG

#ifdef DEBUG
	#define PRINT_RUN \
		print_start_func(__func__);
	#define PRINT_END \
		print_end_func(__func__);
#else
	#define PRINT_RUN
	#define PRINT_END
#endif


char *encode(char *string)
{
	PRINT_RUN

	char *new = (char*)malloc(sizeof(string));
	int i;
	// char s[] = "";
	BINTREE *symbols_list = get_symbols_list((unsigned char*)string);
	BINTREE *bin_tree;

	print_list(symbols_list);
	bin_tree = build_bintree(symbols_list);
	print_bintree(bin_tree, "");
	// assign_bintree_values(bin_tree, "");

	PRINT_END
	return new;
}


BINTREE *build_bintree(BINTREE *main_lst)
{
	PRINT_RUN

	BINTREE *new_lst, *left_lst, *right_lst;

	while ((left_lst = pop(&main_lst)) != NULL
		&& (right_lst = pop(&main_lst)) != NULL)
	{
		new_lst = (BINTREE*)malloc(sizeof(BINTREE));
		
		left_lst->code = "1";
		right_lst->code = "0";

		new_lst->left = left_lst;
		new_lst->right = right_lst;
		new_lst->encoded =  NULL;
		new_lst->value = left_lst->value;
		new_lst->count = left_lst->count + right_lst->count;
		new_lst->hash = right_lst->hash - 100;
		
		// print_list(main_lst);
		// print_list(new_lst);
		
		insert(&main_lst, new_lst);

		// print_list(main_lst);
	}
	new_lst->code = "1";

	PRINT_END
	return new_lst;
}


BINTREE *pop(BINTREE **main_lst)
{
	// PRINT_RUN

	BINTREE *lst = (*main_lst);
	
	if ((*main_lst) != NULL)
	{
		*main_lst = (*main_lst)->next;
		lst->next = NULL;
	}

	// PRINT_END
	return lst;
}


int assign_bintree_values(BINTREE *root, char *seq)
{
	PRINT_RUN

	if (root == NULL)
	{
		PRINT_END
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("%c == %s%s\n", (signed)root->value, seq, root->code);
		strcpy(root->encoded, seq);

		PRINT_END
		return 0;
	}
	
	// printf("connect codes [%s %x]\n", root->code, root->value);

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
	
	assign_bintree_values(root->left, left_seq);
	assign_bintree_values(root->right, right_seq);
	
	PRINT_END
}


int print_bintree(BINTREE *root, char *seq)
{
	// PRINT_RUN

	if (root == NULL)
	{
		// PRINT_END
		return 1;
	}

	if ((root->right == NULL)
		&& (root->left == NULL))
	{
		printf("%c == %s%s\n", (signed)root->value, seq, root->code);

		// PRINT_END
		return 0;
	}
	
	// printf("connect codes [%s %x]\n", root->code, root->value);

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
	
	// PRINT_END
}


BINTREE *get_symbols_list(unsigned char *string)
{
	PRINT_RUN

	BINTREE *symbols_list = (BINTREE*)malloc(sizeof(BINTREE));
	int i;
	
	// printf("%x - %s\n", string, (signed)string);
	// print_list(symbols_list);
	for (i = 0; i < strlen(string); i++)
	{
		// printf("%x - %c\n", (unsigned)string[i], string[i]);
		append(symbols_list, get_hash(string[i]), string[i]);
	}
	
	PRINT_END
	return symbols_list->next;
}


int get_hash(unsigned char symbol)
{
	// PRINT_RUN

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

	// PRINT_END
	return hash;
}


void print_list(BINTREE *list)
{
	// PRINT_RUN

	BINTREE *nxt_lst = list;

	printf("[\n");
	while (nxt_lst != NULL)
	{
		// printf("%d - ", nxt_lst);
		printf("%05d : %02x (%d)\n", nxt_lst->hash, nxt_lst->value, nxt_lst->count);
		nxt_lst = nxt_lst->next;
	}
	printf("]\n");

	// PRINT_END
}


int append(BINTREE *main_lst, int hash, unsigned char value)
{
	// PRINT_RUN
	
	BINTREE *left_lst = main_lst, *right_lst = main_lst->next;
	BINTREE *new_lst = (BINTREE*)malloc(sizeof(BINTREE));

	new_lst->left = new_lst->right = new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->count = 1;
	new_lst->code = "0";
	new_lst->value = value;

	if (left_lst == NULL)
	{
		main_lst = new_lst;

		// PRINT_END
		return 0;
	}

	while (right_lst != NULL)
	{
		if (value == right_lst->value)
		{
			right_lst->count += 1;
			left_lst->next = right_lst->next;	
			insert(&main_lst, right_lst);

			// PRINT_END
			return 0;
		}
		left_lst = right_lst;
		right_lst = right_lst->next;
	}
	insert(&main_lst, new_lst);

	// PRINT_END
	return 0;
}


int insert(BINTREE **main_lst, BINTREE *new_lst)
{
	// PRINT_RUN
	
	BINTREE *left_lst = (*main_lst), *right_lst;

	// printf("Inserting [%02x (%d)] in\n", new_lst->value, new_lst->count);

	if (left_lst == NULL)
	{
		*main_lst = new_lst;
		
		// PRINT_END
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
	
	// PRINT_END
	return 0;
}
