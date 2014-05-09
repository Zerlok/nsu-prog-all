#include "haf.h"

#include "../debug_trar.h"
#define DEBUG

#ifdef DEBUG
	#define PRINT_START \
		print_start_func(__func__);
	#define PRINT_END \
		print_end_func(__func__);
#else
	#define PRINT_START
	#define PRINT_END
#endif


char *encode(char *string)
{
	PRINT_START

	char *new = (char*)malloc(sizeof(string));
	int i;
	char s[] = "<<<";
	BINTREE *symbols_list = get_symbols_list((unsigned char*)string);
	BINTREE *bin_tree;

	print_list(symbols_list);
	bin_tree = build_bintree(symbols_list);
	decorate("bin_tree created");
	// print_list(pop(symbols_list));
	print_list(symbols_list);
	// printf("code: %d", bin_tree->hash);

	PRINT_END
	return new;
}


BINTREE *build_bintree(BINTREE *main_lst)
{
	PRINT_START

	BINTREE *new_lst, *left_lst, *right_lst;
	int i = 0;
	while (i < 10
        // && ((left_lst = pop(&main_lst)) != NULL)
        && (main_lst != NULL)
		)
	{
		left_lst = pop(&main_lst);
		new_lst = (BINTREE*)malloc(sizeof(BINTREE));
		
		left_lst->code = "1";
		new_lst->left = left_lst;
		new_lst->right = right_lst;
		new_lst->value = left_lst->value;
		
        if ((right_lst = pop(&main_lst)) != NULL)
		{
			right_lst->code = "0";
			new_lst->count = left_lst->count + right_lst->count;
            new_lst->hash = right_lst->hash - 100;
		}
        else
		{
			new_lst->count = left_lst->count;
			new_lst->hash = left_lst->hash + 200;
		}
		
		if (left_lst != NULL)
		{
			printf("pop result: list (%d)\n", left_lst->hash);
		}
		else
		{
			printf("pop result: NULL\n");
		}
		if (right_lst != NULL)
		{
			printf("pop result: list (%d)\n", right_lst->hash);
		}
		else
		{
			printf("pop result: NULL\n");
		}
		print_list(main_lst);
		print_list(new_lst);
		
		insert(&main_lst, new_lst);

		print_list(main_lst);
		i++;
	}
	print_decor();

	PRINT_END
	return new_lst;
}


BINTREE *pop(BINTREE **main_lst)
{
	PRINT_START
	// if ()
	// {
	// 	return NULL;
	// }

	BINTREE *lst = *main_lst;
	printf(">> %u\n", *main_lst);
	if ((*main_lst) != NULL)
	{
		*main_lst = (*main_lst)->next;
		(lst->next) = NULL;
	}

	PRINT_END
	return lst;
}


BINTREE *get_trunk(char *code, BINTREE *list)
{
	PRINT_START
	
	if (list == NULL)
	{
		PRINT_END
		return NULL;
	}

	BINTREE *root = (BINTREE*)malloc(sizeof(BINTREE));
	root->left = root->right = NULL;
	strcpy(root->code, code);

	PRINT_END
	return root;
}


int print_bintree(BINTREE *root, char *seq)
{
	PRINT_START

	// char *left_seq = (char*)malloc(sizeof(seq));
	// char *right_seq = (char*)malloc(sizeof(seq));
	char *left_seq, *right_seq;

	// strcpy(left_seq, seq);
	// strcpy(right_seq, seq);
	if (root != NULL)
	{
		// printf("connect codes [%s %x]\n", root->code, root->value);
		if ((root->right == NULL)
			&& (root->left == NULL))
		{
			printf("%s+%s %x\n", seq, root->code, root->value);
			return 0;
		}
		if (root->left != NULL)
		{
			// decorate(seq);
			print_decor();
			printf("%d\n", root->hash);
			left_seq = strcat(seq, root->code);
			print_bintree(root->left, left_seq);
		}
		if (root->right != NULL)
		{
			right_seq = strcat(seq, root->code);
			print_bintree(root->right, strcat(right_seq, root->code));
		}
	}
	
	PRINT_END
	return 0;
}


BINTREE *get_symbols_list(unsigned char *string)
{
	PRINT_START

	BINTREE *symbols_list = (BINTREE*)malloc(sizeof(BINTREE));
	// BINTREE *symbols_list;
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


void print_list(BINTREE *list)
{
	// PRINT_START

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
	// PRINT_START
	
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
	PRINT_START
	
	BINTREE *left_lst = (*main_lst), *right_lst;

	// printf("Inserting [%02x (%d)] in\n", new_lst->value, new_lst->count);

	if (left_lst == NULL)
	{
		*main_lst = new_lst;
		
		PRINT_END
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
	
	PRINT_END
	return 0;
}
