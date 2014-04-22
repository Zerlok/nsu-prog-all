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

	SYMLIST *symbols_list = (SYMLIST*)malloc(sizeof(SYMLIST));
	// SYMLIST *symbols_list = NULL;
	int i;
	
	// printf("%x - %s\n", string, (signed)string);
	// print_list(symbols_list);
	for (i = 0; i < strlen(string); i++)
	{
		// printf("%x - %c\n", (unsigned)string[i], string[i]);
		append(symbols_list, get_hash(string[i]), string[i]);
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
	// printf("%d\n", nxt_ls);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


int append(SYMLIST *main_lst, int hash, unsigned char value)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	SYMLIST *left_lst = main_lst, *right_lst = main_lst->next;
	SYMLIST *new_lst = (SYMLIST*)malloc(sizeof(SYMLIST));

	new_lst->next = NULL;
	new_lst->hash = hash;
	new_lst->value = value;
	new_lst->count = 1;

	if (left_lst == NULL)
	{
		main_lst = new_lst;
		// printf("insert right_lst : %d\n", right_lst);
		// printf("new_lst is :%d\n", &new_lst);
		// printf("list is : %d\n", list);
		#ifdef DEBUG
			print_end_func(__func__);
		#endif
		return 0;
	}

		// && (value != right_lst->value))
	while (right_lst != NULL)
	{
		if (value == right_lst->value)
		{
			right_lst->count += 1;
			left_lst->next = right_lst->next;	
			insert(main_lst, right_lst);
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


int insert(SYMLIST *main_lst, SYMLIST *new_lst)
{
	#ifdef DEBUG
		print_start_func(__func__);
	#endif
	
	SYMLIST *left_lst = main_lst, *right_lst = main_lst->next;

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
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif
	return 0;
}
