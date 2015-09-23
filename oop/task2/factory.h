#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <stdarg.h>


typedef struct _List
{
	Class cls;

	char *key;
	void *value;
	void *next;

	int (*appender)(void *_self, char *key, void *value);
	void *(*getter)(void *_self, char *key);
	void (*printor)(void *_self);
} ListStruct;


void *List_constructor(void *_self, va_list *args);
void List_destructor(void *_self);

int List_appender(void *_self, char *key, void *value);
void *List_getter(void *_self, char *key);
void List_printor(void *_self);

int lst_append(void *_self, char *key, void *value);
void *lst_get(void *_self, char *key);


// ------------------ FACTORY ------------------ //

typedef struct _Factory
{
	Class cls;

	void *data;

	int (*registrator)(void *_self, char *key, Class *cls);
	void *(*creator)(void *_self, ...);
} FactoryStruct;


void *Factory_constructor(void *_self, va_list *args);
void Factory_destructor(void *_self);

int Factory_registrator(void *_self, char *key, Class *cls);
void *Factory_creator(void *_self, ...); // self, key, *args.

int fct_register(void *_self, char *key, Class *cls);
void *fct_create(void *_self, char *key);

extern void *Factory;


// __FACTORY_H__
#endif
