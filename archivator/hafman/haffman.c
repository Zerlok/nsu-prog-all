#include "haf.h"

#include "../debug.h"
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

	BINTREE *symbols_list = get_symbols_list((unsigned char*)string);
	#ifdef DEBUG
		print_list(symbols_list);
	#endif
	
	BINTREE *bin_tree = get_bintree(symbols_list);;
	#ifdef DEBUG
		print_bintree(bin_tree, "");
	#endif

	count_bintree_codes(bin_tree, "");

	for (i = 0; i < strlen(string); i++)
	{
		new = strcat(new, get_encoded(symbols_list, string[i]));
		// printf("%s ", get_encoded(symbols_list, string[i]));
	}
	// printf("\n");

	#ifdef DEBUG
		// printf("decode is: '%s'\n", decode(bin_tree, new));
		decode(bin_tree, new);
	#endif

	PRINT_END
	return new;
}


int decode(BINTREE *root, char *string)
{
	PRINT_RUN

	int i;
	// char *new = (char*)malloc(sizeof(string));
	BINTREE *head = root;

	if (root == NULL)
	{
		PRINT_END
		return 1;
	}

	// strcpy(new, "");
	printf("Decode is: ");

	for (i = 0; i < strlen(string); i++)
	{
		if ((head->left == NULL) && (head->right == NULL))
		{
			// strcat(new, (char)head->value);
			printf("%c", (signed)head->value);
			head = root;
		}
		if (string[i] == '1')
		{
			head = head->left;
		}
		else if (string[i] == '0')
		{
			head = head->right;
		}
		else
		{
			decorate("EXSEPTION!@@P");
			exit(1);
		}
	}
	
	if (root->left != NULL && root->right != NULL)
	{
		printf("%c", (signed)head->value);
	}

	printf("\n");
	PRINT_END
	return 0;
}


char *get_encoded(BINTREE *main_lst, unsigned char symbol)
{
	// PRINT_RUN

	BINTREE *lst = main_lst;

	// printf("'%c'\n", (signed)symbol);

	while (lst != NULL)
	{
		if (lst->value == symbol)
		{
			// PRINT_END
			return lst->encoded;
		}

		lst = lst->next;
	}

	// PRINT_END
	return NULL;
}


BINTREE *get_bintree(BINTREE *main_lst)
{
	PRINT_RUN

	BINTREE *new_lst, *left_lst, *right_lst, *header = main_lst;

	if (header->next == NULL)
	{
		header->left = header->right = NULL;
		header->code = "0";
		return header;
	}

	while ((left_lst = pop_list(&header)) != NULL
		&& (right_lst = pop_list(&header)) != NULL)
	{
		new_lst = (BINTREE*)malloc(sizeof(BINTREE));
		
		left_lst->code = "1";
		right_lst->code = "0";

		new_lst->left = left_lst;
		new_lst->right = right_lst;
		new_lst->hash = 1;
		new_lst->value = (unsigned)"";
		new_lst->count = left_lst->count + right_lst->count;
		
		// print_list(main_lst);
		// print_list(new_lst);
		
		insert_to_list(&header, new_lst);

		// print_list(main_lst);
	}
	new_lst->code = "";
	insert_to_list(&main_lst, new_lst);

	PRINT_END
	return new_lst;
}


int count_bintree_codes(BINTREE *root, char *seq)
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
		root->encoded = (char*)malloc(sizeof(seq));
		strcpy(root->encoded, seq);
		// printf("assigned %c == %s+%s", (signed)root->value, seq, root->code);
		// printf(" | strcat == (%s)\n", strcat(seq, root->code));
		// printf("\n");

		strcat(root->encoded, root->code);

		// PRINT_END
		return 0;
	}
	
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
	
	count_bintree_codes(root->left, left_seq);
	count_bintree_codes(root->right, right_seq);
	
	// PRINT_END
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
		append_list(symbols_list, get_hash(string[i]), string[i]);
	}
	
	PRINT_END
	return symbols_list->next;
}


BINTREE *pop_list(BINTREE **main_lst)
{
	// PRINT_RUN

	BINTREE *lst = (*main_lst);
	
	if ((*main_lst) != NULL)
	{
		*main_lst = (*main_lst)->next;
		// lst->next = NULL;
	}

	// PRINT_END
	return lst;
}


int append_list(BINTREE *main_lst, int hash, unsigned char value)
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
			insert_to_list(&main_lst, right_lst);

			// PRINT_END
			return 0;
		}
		left_lst = right_lst;
		right_lst = right_lst->next;
	}
	insert_to_list(&main_lst, new_lst);

	// PRINT_END
	return 0;
}


int insert_to_list(BINTREE **main_lst, BINTREE *new_lst)
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


void print_list(BINTREE *main_lst)
{
	// PRINT_RUN

	BINTREE *lst = main_lst;

	printf("[\n");
	while (lst != NULL)
	{
		if (lst->hash == 1)
		{
			printf("[1 : %x (%d)]\n", lst->value, lst->count);
		}
		else
		{
			printf("%05d : %x (%d)\n", lst->hash, lst->value, lst->count);
		}

		lst = lst->next;
	}
	printf("]\n");

	// PRINT_END
}
