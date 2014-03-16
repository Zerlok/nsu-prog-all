/* MODULES */
#include <stdio.h>
#include <string.h>


/* APPLICATION VARS */
#define ARC_NAME "Trarchive"
#define VERSION "0.01"
#define DEBUG


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
#define TEST_CODE 40
#define HELP_CODE 50


/* ERRORS > 99 */
#define ERROR_CODE 99
#define ERR_UNKNOWN_FLAG 100
#define ERR_NO_FLAG_ARG 200
#define ERR_NOT_ARCH_FILE 300


/* FUNCTION IMAGES */
void print_doc();
void print_flag_help();
void print_err(int err_code);
void print_flag(char flag[]);
void view_decor();

int read_tags(int argc, char *argv[]);
