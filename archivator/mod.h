/* MODULES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* APPLICATION VARS */

#define ARC_NAME "Trarchive"
#define VERSION "0.01"
#define DEBUG


/* DEBUG */
#ifdef DEBUG

void print_flag(char flag[]);
void print_func_name(char name[]);
void print_decor();
void decorate(char str[]);
void run_test();

#define TESTMODE_FLAG "--test"
#define TESTMODE_CODE 9000
#define TESTMODE_ERROR -9000

#endif


/* FILE VARS*/

#define ARC_FILE_TAG ".trar"


/* FLAGS */

#define FLAG_ADD "-a"
#define FLAG_EXTR "-x"
#define FLAG_LIST "-l"
#define FLAG_TEST "-t"
#define FLAG_HELP "--help"


/* FUNCTION CODES < 100 */

#define APPEND_CODE 10
#define EXTRACT_CODE 20
#define LIST_CODE 30
#define TESTSUM_CODE 40
#define HELP_CODE 50


/* ERRORS > 99 */

#define ERROR_CODE 99
#define ERR_UNKNOWN_FLAG 100
#define ERR_NO_FLAGS 200
#define ERR_NO_FLAG_ARG 300
#define ERR_NOT_ARCH_FILE 400


/* FUNCTION IMAGES */

void print_doc();
void print_flag_help();
void print_err(int err_code);

int read_tags(int argc, char *argv[]);
