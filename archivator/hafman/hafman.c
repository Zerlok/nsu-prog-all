#include "haf.h"

#include "../debug_trar.h"
#define DEBUG_


char *encode(char *string)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	char *new = (char*)malloc(sizeof(string));
	int i;
	SYMLIST *symbols_list = get_symbols_list((unsigned char*)string);

	print_list(symbols_list);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return new;
}


SYMLIST *get_symbols_list(unsigned char *string)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif

	// SYMLIST *symbols_list = (SYMLIST*)malloc(sizeof(SYMLIST));
	SYMLIST *symbols_list = NULL;
	int i;
	
	printf("%x - %s\n", string, (signed)string);
	print_list(symbols_list);
	for (i = 0; i < strlen(string); i++)
	{
		insert(&symbols_list, get_hash(string[i]), string[i]);
		// print_list(symbols_list);
	}
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	
	return symbols_list;
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
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	SYMLIST *nxt_lst = list;

	printf("[\n");
	while (nxt_lst != NULL)
	{
		printf("%d - ", nxt_lst);
		printf("%05d : %02x (%d)\n", nxt_lst->hash, nxt_lst->value, nxt_lst->count);
		nxt_lst = nxt_lst->next;
	}
	printf("]\n");

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


int insert(SYMLIST **list, int hash, unsigned char value)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	SYMLIST *left_lst, *right_lst = (*list);
	SYMLIST *new_lst = (SYMLIST*)malloc(sizeof(SYMLIST));

	new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->value = value;
	new_lst->count = 1;


	if (right_lst == NULL)
	{
		list = &new_lst;

		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return 0;
	}

	left_lst = right_lst;
	// right_lst = right_lst->next;
	// printf("%d\n", right_lst);
	while (right_lst != NULL)
	{
		if (hash == right_lst->hash)
		{
			if (value == right_lst->value)
			{
				right_lst->count += 1;
				left_lst->next = right_lst->next;
				
				shift_list(list, right_lst);

				#ifdef DEBUG
					print_end_func(__func__);
				#endif
				return 0;
			}
			else
			{
				printf("Collision!!!\nHash : '%d' for values : (%x) (%x)\n", hash, value, right_lst->value);
				return 0;
			}
		}	
		left_lst = right_lst;
		right_lst = right_lst->next;
		// printf("%d\n", right_lst);
	}
	// print_decor();
	
	left_lst->next = new_lst;

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	return 0;
}


int shift_list(SYMLIST **list, SYMLIST *new_lst)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	SYMLIST *left_lst, *right_lst = (*list);
	
	if (right_lst == NULL)
	{
		printf("right_lst is NULL!\n");
		return 0;
	}

	if (right_lst->count < new_lst->count)
	{
		new_lst->next = right_lst;
		list = &new_lst;

		#ifdef DEBUG
			print_end_func(__func__);
		#endif
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

			#ifdef DEBUG
				print_end_func(__func__);
			#endif
			return 0;
		}
		left_lst = right_lst;
		right_lst = right_lst->next;
	}
	
	left_lst->next = new_lst;

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	return 0;
}