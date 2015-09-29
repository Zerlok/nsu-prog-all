#ifndef __EXTRASTRING_H__
#define __EXTRASTRING_H__


#include <string.h>
#include "../task1/recordarray.h"


typedef RecordArray StringArray;


void (*sa_print)(StringArray *strings);
void (*sa_delete)(StringArray *strings);

StringArray *sa_create(size_t size);
void sa_set(StringArray *strings, size_t idx, char *string);
char *sa_get(StringArray *strings, size_t idx);


StringArray *str_split(char *string, char *chr);


//__EXTRASTRING_H__
#endif
