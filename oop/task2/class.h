#ifndef __CLASS_H__
#define __CLASS_H__


#include <stddef.h>
#include <stdarg.h>


typedef struct _Class
{
	size_t size;
	
	void *(*constructor)(void *_class, va_list *args);
	void (*initializer)(void *_self, int argn, char **args);
	void (*destructor)(void *_self);
	void (*printor)(void *_self);
} Class;


void *new_object(void *_class, ...);
void initialize_object(void *ptr_obj, int argn, char **args);
void delete_object(void *ptr_obj);
void print(void *ptr_obj);


// __CLASS_H__
#endif
