/* MODULES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hafman/haf.h"


/* ARCHIVE */
typedef struct Archive
{
	char version[5]; // The version of archive
	char *name; // The path and name of archive
	int files_count; // The number of files
	ARCHIVEDFILE **files; // The list of added files
} ARCHIVE;


/* ARCHIVE VARS */
#define ARC_NAME "Trarchive"
#define ARC_VERSION "v0.01"
#define DEBUG


/* FILE VARS*/
#define ARC_FILE_TAG ".trar"


/* DEBUG */
#ifdef DEBUG
	#define TESTMODE_FLAG "--test"
	#define TESTMODE_CODE 9000
	#define TESTMODE_ERROR -9000

	int run_test(char *file_name);

#endif

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

/* FLAG ERRORS */
#define ERROR_CODE 99
#define ERR_UNKNOWN_FLAG 100
#define ERR_NO_FLAGS 200
#define ERR_NO_FLAG_ARG 300
#define ERR_NOT_ARCH_FILE 400
#define ERR_ARCH_DOES_NOT_EXIST 500
#define ERR_UNSUPPORTED_VERSION 600


/* FUNCTION IMAGES */
void print_bin_file(char *file_name);
int is_an_archive(char *file_name);
int is_in_archive(char *file_name, ARCHIVE *archive);

int read_or_create_an_archive(char *arch_name, ARCHIVE *arch);
int write_an_archive_to_file(ARCHIVE *arch);

int add_to_archive(char *file_name, ARCHIVE *arch);
int extract_file_from_archive(char *file_name, ARCHIVE *archive);
int show_archived_files(ARCHIVE *archive);

BINTREE *get_bintree_from_file(FILE *file, unsigned long int length);
//unsigned long int build_bintree_from_file(FILE *file, BINTREE *root, unsigned long int length, char *code);
