#ifndef __PARSER_H__
#define __PARSER_H__


#define SAVE_DATA ({\
	if (data_len != 0)\
	{\
		push_into_string_array(data, array);\
		bzero(data, data_len);\
		data_len = 0;\
		is_string = 0;\
	}\
})

StringArray *split(char *line);


// __PARSER_H__
#endif
