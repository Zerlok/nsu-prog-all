#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "list.h"


void *List_constructor(void *_self, va_list *args)
{
	ListStruct *self = _self;

	self->key = va_arg(args, char*);
	self->value = va_arg(args, void*);
	self->next = NULL;

	self->appender = List_appender;
	self->getter = List_getter;

	return self;
}


void List_destructor(void *_self)
{
	ListStruct *curr_lst = _self;
	ListStruct *next_lst;

	while (curr_lst->next != NULL)
	{
		next_lst = curr_lst->next;
		free(curr_lst);
		curr_lst = next_lst;
	}
}


void List_printor(void *_self)
{
	ListStruct *lst = _self;

	while (lst != NULL)
	{
		printf("'%s' ", lst->key);
		lst = lst->next;
	}
}


int List_appender(void *_self, char *key, void *value)
{
	ListStruct *curr_lst = _self;
	ListStruct *prev_lst;

	if (curr_lst->key == NULL)
	{
		curr_lst->key = key;
		curr_lst->value = value;
		return 1;
	}

	while (curr_lst != NULL)
	{
		if (!strcmp(curr_lst->key, key))
			return 0;

		prev_lst = curr_lst;
		curr_lst = curr_lst->next;
	}

	prev_lst->next = new_object(List, key, value);
	return 1;
}


void *List_getter(void *_self, char *key)
{
	ListStruct *lst = _self;

	while (lst != NULL)
	{
		if (!strcmp(lst->key, key))
			return lst->value;

		lst = lst->next;
	}

	return NULL;
}


int lst_append(void *_self, char *key, void *value)
{
	if ((_self == NULL)
			|| (key == NULL)
			|| (value == NULL)
		) return 0;

	ListStruct *lst = _self;
	return lst->appender(_self, key, value);
}


void *lst_get(void *_self, char *key)
{
	if ((_self == NULL)
			|| (key == NULL)
		) return NULL;

	ListStruct *lst = _self;
	return lst->getter(_self, key);
}


Class ListClass = {
	sizeof(ListStruct),
	List_constructor,
	NULL,
	List_destructor,
	List_printor
};


void *List = &ListClass;
