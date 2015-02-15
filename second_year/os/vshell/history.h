#ifndef __HISTORY_H__
#define __HISTORY_H__


#define HISTORY_EXPANDING_CRITERIA 2


typedef struct StringArray
{
	size_t allocated_length;
	size_t used_length;
	char **data;
} History;


History *get_history(int length);
void check_length_and_expand_history(History *history);
void push_into_history(char *string, History *history);
void show_history(History *history);


// __HISTORY_H__
#endif