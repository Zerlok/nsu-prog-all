#ifndef __CLASS_H__
#define __CLASS_H__


typedef struct _Class {
	size_t size;
	
	void *(*constructor)(void *_object, va_list *app);
	void *(*destructor)(void *_object);
} Class;


void *new(void *_class, ...);
void delete(void *_object);

// __CLASS_H__
#endif
