#ifndef __CLASS_H__
#define __CLASS_H__


typedef struct _Class {
	size_t size;
	
	void *(*constructor)(void *_class, va_list *args);
	void (*destructor)(void *_class);
	void (*printor)(void);
} Class;


void *new(void *_class, va_list *args);
void delete(void *ptr_obj);
void print(void *ptr_obj);

// __CLASS_H__
#endif
