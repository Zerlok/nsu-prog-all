#ifndef __CLASS_H__
#define __CLASS_H__


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef struct _Class {
	size_t size;
	
	void *(*constructor)(void *_class, ...);
	void (*destructor)(void *_self);
	void (*printor)(void *_self);
} Class;


void *new(void *_class, ...);
void delete(void *ptr_obj);
void print(void *ptr_obj);

// __CLASS_H__
#endif
