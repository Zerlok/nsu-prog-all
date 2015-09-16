#ifndef __CLASS_H__
#define __CLASS_H__


typedef struct _Class {
	size_t size;
	
	void *(*constructor)(void *self, va_list *app);
	void *(*destructor)(void *self);
} Class;


// __CLASS_H__
#endif
