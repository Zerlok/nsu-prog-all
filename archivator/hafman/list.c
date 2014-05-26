#include "haf.h"


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
