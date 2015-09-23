#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "factory.h"


Class ListClass = {
	sizeof(ListStruct),
	List_constructor,
	List_destructor,
	List_printor
};


void *List = &ListClass;


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
		printf("(%s - %p), ", lst->key, lst->value);
}


int List_appender(void *_self, char *key, void *value)
{
	ListStruct *lst = _self;

	if (lst->key == NULL)
	{
		lst->key = key;
		lst->value = value;
		return 1;
	}

	while (lst->key != NULL)
	{
		if (!strcmp(lst->key, key))
			return 0;

		lst = lst->next;
	}

	lst->next = new_object(List, key, value);
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


// ------------------ FACTORY ------------------ //

void *Factory_constructor(void *_self, va_list *args)
{
	FactoryStruct *self = _self;
	self->data = new_object(List, NULL, NULL);

	self->registrator = Factory_registrator;
	self->creator = Factory_creator;

	return self;
}


void Factory_destructor(void *_self)
{
	FactoryStruct *self = _self;
	delete_object(self->data);
}


int Factory_registrator(void *_self, char *key, Class *cls)
{
	FactoryStruct *self = _self;
	return lst_append(self->data, key, cls);
}


void *Factory_creator(void *_self, ...)
{
	FactoryStruct *self = _self;

	va_list args;
	va_start(args, _self);
	char *key = va_arg(args, char*);

	Class *cls = lst_get(self->data, key);
	return new_object(cls);
}


int fct_register(void *_self, char *key, Class *cls)
{
	FactoryStruct *fct = _self;
	return fct->registrator(_self, key, cls);
}


void *fct_create(void *_self, char *key)
{
	FactoryStruct *fct = _self;
	return fct->creator(_self, key);
}


Class FactoryClass = {
	sizeof(FactoryStruct),
	Factory_constructor,
	Factory_destructor,
	NULL
};


void *Factory = &FactoryClass;
