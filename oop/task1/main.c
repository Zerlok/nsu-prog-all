#include <stdio.h>
#include <stdlib.h>
#include "longstring.h"


int main(int argc, char **argv)
{
	t_longstring *text = get_longstring("Input text is:\n\0");
	t_longstring *double_paragraph = get_longstring("\n\n\0");

	while (!is_endswith_longstring(text, double_paragraph))
		append_longstring(text, getchar());

	print_longstring(text);

	destroy_longstring(text);
	destroy_longstring(double_paragraph);
	return 0;
}
