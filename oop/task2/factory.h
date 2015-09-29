#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <stdarg.h>

#include "extrastring.h"


typedef struct _Factory
{
	Class *cls;

	void *data;

	int (*registrator)(void *_self, char *key, Class *cls);
	void *(*creator)(void *_self, char *key);
} FactoryStruct;


void *Factory_constructor(void *_self, va_list *args);
void Factory_destructor(void *_self);

int Factory_registrator(void *_self, char *classname, Class *cls);
void *Factory_creator(void *_self, char *classname);

int fct_register(void *_self, char *key, Class *cls);
void *fct_create(void *_self, int argn, char **args);


extern void *Factory;


// __FACTORY_H__
#endif
