#ifndef __LIST_H__
#define __LIST_H__


#include <stdarg.h>


typedef struct _List
{
	Class *cls;

	char *key;
	void *value;
	void *next;

	int (*appender)(void *_self, char *key, void *value);
	void *(*getter)(void *_self, char *key);
} ListStruct;


void *List_constructor(void *_self, va_list *args);
void List_destructor(void *_self);

int List_appender(void *_self, char *key, void *value);
void *List_getter(void *_self, char *key);
void List_printor(void *_self);

int lst_append(void *_self, char *key, void *value);
void *lst_get(void *_self, char *key);


extern void *List;


// __LIST_H__
#endif
