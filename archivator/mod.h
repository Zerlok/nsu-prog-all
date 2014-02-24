/* MODULES */
#include <stdio.h>


/* APPLICATION VARS */
#define ARC_NAME "Trarchive"
#define VERSION "0.01"


/* FLAGS */
#define FLAG_ADD "-a"
#define FLAG_EXTR "-x"
#define FLAG_LIST "-l"
#define FLAG_TEST "-t"


/* ERRORS */
#define ERR_NO_TAG_ARG 100


/* FUNCTION IMAGES */
void print_doc();
void print_err(int err_code);
void print_tag(char tag[]);

int read_tags(int argc, char *argv[]);
