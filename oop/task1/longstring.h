#ifndef __LONGSTRING_H__
#define __LONGSTRING_H__


#define _LONGSTRING_EXPAND_CRITERIA (32)


typedef struct _longstring
{
	unsigned long long int m_size;
	unsigned long long int m_index;
	char *m_data;
} t_longstring;


t_longstring *get_longstring(char *data);
void init_data_longstring(t_longstring *longstring);
void check_and_expand_longstring(t_longstring *longstring);
void append_longstring(t_longstring *longstring, char chr);
int is_endswith_longstring(t_longstring *working_string, t_longstring *comparing_string);
void print_longstring(t_longstring *longstring);
void destroy_longstring(t_longstring *longstring);


// __LONGSTRING_H__
#endif