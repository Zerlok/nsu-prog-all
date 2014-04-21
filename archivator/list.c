#include "mod.h"


void print_list(struct List *list)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	struct List *nxt_lst = list;

	printf("[");
	while (nxt_lst)
	{
		printf("(%d : 02%x) ", nxt_lst->hash, nxt_lst->value);
		nxt_lst = nxt_lst->next;
	}
	printf("]\n");

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


void delete_list(struct List *list)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif
	
	struct List *lst = list, *nxt;

	while (lst)
	{
		nxt = lst->next;
		free(lst);
		lst = nxt;
	}

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


int insert(struct List **list, int hash, unsigned char value)
{
	// #ifdef DEBUG
	// 	print_func_name(__func__);
	// #endif
	
	struct List *left_lst, *right_lst = (*list);
	struct List *new_lst = (struct List*) malloc (sizeof(struct List));

	
	new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->value = value;
	new_lst->count = 1;


	if (right_lst == NULL)
	{
		list = &new_lst;
		
		// #ifdef DEBUG
		// 	print_end_func(__func__);
		// #endif

		return 0;
	}

	left_lst = right_lst;
	//right_lst = right_lst->next;

	while (right_lst != NULL)
	{
		if (hash == right_lst->hash)
		{
			if (value == right_lst->value)
			{
				right_lst->count += 1;
				left_lst->next = right_lst->next;
				
				shift_list(list, &right_lst);

				// #ifdef DEBUG
				// 	print_end_func(__func__);
				// #endif
				
				return 0;
			}
			else
			{
				decorate("COLLISION!");

				printf("Hash : '%d' for values : (%x) (%x)\n", hash, value, right_lst->value);
				
				#ifdef DEBUG
					print_end_func(__func__);
				#endif

				return 0;
			}
		}
		// else
		// {
		// 	// printf("!");
		// }
		
		left_lst = right_lst;
		right_lst = right_lst->next;
		// printf("%d\n", right_lst);
	}
	// decorate("hello");
	
	left_lst->next = new_lst;

	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif

	return 0;
}


int shift_list(struct List **list, struct List *new_lst)
{
	// #ifdef DEBUG
	// 	print_func_name(__func__);
	// #endif

	struct List *left_lst, *right_lst = (*list);
	
	if (right_lst == NULL)
	{
		printf("right_lst is NULL!\n");

		// #ifdef DEBUG
		// 	print_end_func(__func__);
		// #endif

		return 0;
	}

	if (right_lst->count < new_lst->count)
	{
		new_lst->next = right_lst;
		(*list) = new_lst;

		// #ifdef DEBUG
		// 	print_end_func(__func__);
		// #endif

		return 0;
	}

	left_lst = right_lst;
	right_lst = right_lst->next;
	
	while (right_lst)
	{
		if (right_lst->count > new_lst->count)
		{
			new_lst->next = right_lst;
			left_lst->next = new_lst;
			
			// #ifdef DEBUG
			// 	print_end_func(__func__);
			// #endif

			return 0;
		}
		left_lst = right_lst;
		right_lst = right_lst->next;
	}
	
	left_lst->next = new_lst;

	// #ifdef DEBUG
	// 	print_end_func(__func__);
	// #endif

	return 0;
}