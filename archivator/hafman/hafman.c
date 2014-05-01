#include "haf.h"

#include "../debug_trar.h"
#define DEBUG


char *encode(char *string)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	char *new = (char*)malloc(sizeof(string));
	int i;
	char s[] = "<<<";
	SYMLIST *symbols_list = get_symbols_list((unsigned char*)string);
	BINTREE *bin_tree = get_bintree(symbols_list);

	print_list(symbols_list);
	print_decor();
	// print_bintree(bin_tree, s);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return new;
}


BINTREE *get_bintree(SYMLIST *main_lst)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	SYMLIST *new_lst, *right_lst, *left_lst = pop(main_lst);
	 // *right_lst = pop(main_lst);
	BINTREE *right_trunk, *left_trunk;

	print_list(main_lst);
	int i = 1;
	while ((i < 2) &&
		(((left_lst = pop(main_lst)) != NULL)
		|| ((right_lst = pop(main_lst)) != NULL))
		)
	{
		print_list(left_lst);
		print_list(right_lst);
		left_trunk = get_trunk("1", left_lst);
		right_trunk = get_trunk("0", right_lst);

		new_lst = (SYMLIST*)malloc(sizeof(SYMLIST));
		// new_lst->count = left_lst->count + right_lst->count;
		// new_lst->hash = right_lst->hash;
		// new_lst->value = left_lst->value;
		new_lst->count = 69;
		new_lst->hash = 696;
		new_lst->value = (unsigned) "123";
		print_list(new_lst);
		
		// insert(main_lst, new_lst);
		i++;
	}

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}
// {
// 	#ifdef DEBUG
// 		print_start_func(__func__);
// 	#endif

// 	SYMLIST *lst = main_lst;
// 	BINTREE *root, *trunk = get_trunk("0", (unsigned)"");
// 	// *root = get_trunk("1", (unsigned)"");
// 	// root->left = trunk;
// 	// root->right = NULL;

// 	if (lst == NULL)
// 	{
// 		return trunk;
// 	}
// 	trunk->left = get_trunk("1", lst->value);

// 	// if (lst->next == NULL)
// 	// {
// 	// 	return trunk;
// 	// }
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		trunk->right = get_trunk("0", lst->value);
		
// 		root = get_trunk("1", (unsigned)"");
// 		root->left = trunk;
// 		root->right = NULL;
		
// 		lst = lst->next;
// 	}
	
// 	#ifdef DEBUG
// 		print_end_func(__func__);
// 	#endif

// 	return root;
// }


BINTREE *get_trunk(char *code, SYMLIST *list)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	if (list == NULL)
	{
		// free(root);
		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return NULL;
	}

	BINTREE *root = (BINTREE*)malloc(sizeof(BINTREE));
	root->left = root->right = NULL;
	strcpy(root->code, code);
	// root->value = list->value;
	// print_decor();

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	return root;
}


int print_bintree(BINTREE *root, char *seq)
{
	// #ifdef DEBUG
	// 	print_start_func(__func__);
	// #endif

	char *left_seq = (char*)malloc(sizeof(seq));
	char *right_seq = (char*)malloc(sizeof(seq));

	strcpy(left_seq, seq);
	strcpy(right_seq, seq);

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
			print_bintree(root->left, strcat(left_seq, root->code));
		}
		if (root->right != NULL)
		{
			print_bintree(root->right, strcat(right_seq, root->code));
		}
	}

	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif

	return 0;
}


SYMLIST *get_symbols_list(unsigned char *string)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	SYMLIST *symbols_list = (SYMLIST*)malloc(sizeof(SYMLIST));
	// SYMLIST *symbols_list;
	int i;
	
	// printf("%x - %s\n", string, (signed)string);
	// print_list(symbols_list);
	for (i = 0; i < strlen(string); i++)
	{
		// printf("%x - %c\n", (unsigned)string[i], string[i]);
		append(symbols_list, get_hash(string[i]), string[i]);
	}
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	
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


void print_list(SYMLIST *list)
{
	// #ifdef DEBUG
	// 	print_start_func(__func__);
	// #endif
	
	SYMLIST *nxt_lst = list;

	printf("[\n");
	while (nxt_lst != NULL)
	{
		// printf("%d - ", nxt_lst);
		printf("%05d : %02x (%d)\n", nxt_lst->hash, nxt_lst->value, nxt_lst->count);
		nxt_lst = nxt_lst->next;
	}
	printf("]\n");

	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif
}


int append(SYMLIST *main_lst, int hash, unsigned char value)
{
	// #ifdef DEBUG
	// 	print_start_func(__func__);
	// #endif
	
	SYMLIST *left_lst = main_lst, *right_lst = main_lst->next;
	SYMLIST *new_lst = (SYMLIST*)malloc(sizeof(SYMLIST));

	new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->value = value;
	new_lst->count = 1;

	if (left_lst == NULL)
	{
		main_lst = new_lst;

		// #ifdef DEBUG
		// 	print_end_func(__func__);
		// #endif
		return 0;
	}

	while (right_lst != NULL)
	{
		if (value == right_lst->value)
		{
			right_lst->count += 1;
			left_lst->next = right_lst->next;	
			insert(main_lst, right_lst);

			// #ifdef DEBUG
			// 	print_end_func(__func__);
			// #endif
			return 0;
		}
		left_lst = right_lst;
		right_lst = right_lst->next;
	}
	insert(main_lst, new_lst);

	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif
	return 0;
}


int insert(SYMLIST *main_lst, SYMLIST *new_lst)
{
	// #ifdef DEBUG
	// 	print_start_func(__func__);
	// #endif
	
	SYMLIST *left_lst = main_lst, *right_lst = main_lst->next;

	// printf("Inserting [%02x (%d)] in\n", new_lst->value, new_lst->count);

	if (left_lst == NULL)
	{
		main_lst = new_lst;
		
		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return 0;
	}

	while ((right_lst != NULL)
		&& (new_lst->count > right_lst->count))
	{
		left_lst = right_lst;
		right_lst = right_lst->next;
	}

	left_lst->next = new_lst;
	new_lst->next = right_lst;
	
	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif
	return 0;
}


SYMLIST *pop(SYMLIST *main_lst)
{
	SYMLIST *lst = main_lst;

	if ((main_lst == NULL)
		|| (main_lst->next == NULL))
	{
		return NULL;
	}

	main_lst = main_lst->next;
	lst->next = NULL;
	return lst;
}



SYMLIST *exclude(SYMLIST *main_lst, int num)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	SYMLIST *curr_lst, *left_lst = main_lst;

	if (left_lst == NULL)
	{
		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return NULL;
	}

	if (num == 1)
	{
		free(main_lst);

		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return NULL;
	}

	curr_lst = left_lst->next;
	while ((curr_lst != NULL)
		&& (num > 0))
	{
		// if (curr_lst->hash == hash)
		// {
		// 	left_lst->next = curr_lst->next;
		// 	// curr_lst->next = NULL;
			
		// 	#ifdef DEBUG
		// 		print_end_func(__func__);
		// 	#endif
		// 	return curr_lst;
		// }

		left_lst = curr_lst;
		curr_lst = curr_lst->next;
		num -= 1;
	}
	left_lst->next = curr_lst->next;

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	return curr_lst;
}