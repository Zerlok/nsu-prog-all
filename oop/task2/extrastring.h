#ifndef __EXTRASTRING_H__
#define __EXTRASTRING_H__


#include <string.h>
#include "../task1/recordarray.h"


typedef RecordArray String;

void (*str_print)(RecordArray *strings);
void (*str_delete)(RecordArray *strings);

char *str_get(String *strings, size_t idx);


int str_count(char *string, char chr);
String *str_split(char *string, char *chr);


//__EXTRASTRING_H__
#endif
