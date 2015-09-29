#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "list.h"
#include "extrastring.h"
#include "factory.h"


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


int Factory_registrator(void *_self, char *classname, Class *cls)
{
	FactoryStruct *self = _self;
	return lst_append(self->data, classname, cls);
}


void *Factory_creator(void *_self, char *classname)
{
	if (classname == NULL)
		return NULL;

	FactoryStruct *self = _self;
	Class *cls = lst_get(self->data, classname);

	if (cls == NULL)
		return NULL;

	return new_object(cls);
}


int fct_register(void *_self, char *classname, Class *cls)
{
	FactoryStruct *fct = _self;
	return fct->registrator(_self, classname, cls);
}


void *fct_create(void *_self, StringArray *args)
{
	if (args == NULL)
		return NULL;

	FactoryStruct *fct = _self;
	char *classname = sa_get(args, 0);
	void *obj = fct->creator(_self, classname);
	initialize_object(obj, args);

	return obj;
}


Class FactoryClass = {
	sizeof(FactoryStruct),
	Factory_constructor,
	NULL,
	Factory_destructor,
	NULL
};


void *Factory = &FactoryClass;
