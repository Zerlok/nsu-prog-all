#include "mod.h"
//#include "hafman/haf.h"

/* ---------- DEBUG FUNCTIONS ---------- */


int run_test(char *file_name)
{
	FILE *file;
	ARCHIVEDFILE *zipped_file;

	if ((file = fopen(file_name, "rb")) == NULL)
	{
		printf("cannot open the file!\n");
		return 1;
	}

	zipped_file = encode_file(file);
	printf("\nEncoded:\n%s\n\n", zipped_file->text);
	fclose(file);

	return 0;
}


/* ---------- ACCESSORY FUNCTIONS ---------- */


int is_arch_file(char arg[])
/*
If file is an archive file returns 0.
Otherwise returns 1.
Input:
	arg - (*char) the name of file.
*/
{
	if (!strstr(arg, ARC_FILE_TAG)) // If not archive file
		/* TODO: do not skip the '.trarlololo'. '.trar' only! */
	{
		return 1;
	}
	return 0;
}


int read_or_create_an_archive(char *arch_name, ARCHIVE *arch)
/*
Read the archive information to ARCHIVE structure, if archive exist.
Otherwise create the archive struct with basic information.

Input:
	char *arch_name - the name of file
	ARCHIVE *arch - the indicator to archive struct.

Output:
	Return 0 if everything is OK, else 1.
*/
{
	if (is_arch_file(arch_name))
	{
		printf("The file '%s' is not an archive of %s program.\n", arch_name, ARC_NAME);
		exit(1);
	}

	/* Archive init */
	FILE *arch_file;
	arch->name = (char*)calloc(strlen(arch_name) + 1, sizeof(char));
	arch->files = (ARCHIVEDFILE**)calloc(0, sizeof(ARCHIVEDFILE));
	arch->files_count = 0;
	strcpy(arch->version, ARC_VERSION);
	strcpy(arch->name, arch_name);

	if ((arch_file = fopen(arch_name, "r+")) == NULL)
	{
		/* CREATE THE ARCHIVE */
		if ((arch_file = fopen(arch_name, "w")) == NULL)
		{
			printf("Permission denied to the archive '%s'\n", arch_name);
			return 1;
		}
		fclose(arch_file);

		printf("New archive file '%s' created.\n", arch->name);

		return 0;
	}
	fclose(arch_file);

	/* IF ARCHIVE EXIST: */
	printf("Archive file '%s' is already exist.\n", arch->name);
	return 0;
}


/* ---------- ARCHIVE FUNCTIONS ---------- */

void print_bin_file(char *file_name)
{
	FILE *file;
	unsigned char str;
    int i = 1;

	if((file = fopen(file_name, "rb")) == NULL)
	{
		printf("Error while file opening!\n");
		fclose(file);
		exit(1);
	}

    printf("The content of '%s' file:\n", file_name);
	while (fread(&str, sizeof(str), 1, file))
    {
         printf("%02x", str);
         if (!(i % 2)) printf(" ");
         if (!(i % 16)) printf("\n");
         i++;
	}
	printf("\n");

	fclose(file);
}


int add_to_archive(char *file_name, ARCHIVE *arch)
{
	printf("Adding to '%s' archive\n", arch->name);
	ARCHIVEDFILE *zipped_file;
	FILE *file;

	/* Is file exist or readable */
	if ((file = fopen(file_name, "r")) == NULL)
	{
		printf("Permission denied to the file '%s'\n", file_name);
		return 1;
	}
	zipped_file = encode_file(file);
	strcpy(zipped_file->name, file_name);

	/* Appending to archive structure */
	arch->files_count += 1;
	arch->files = (ARCHIVEDFILE**)realloc(arch->files, arch->files_count);
	arch->files[arch->files_count - 1] = zipped_file;

	fclose(file);
	return 0;
}


int write_an_archive_to_file(ARCHIVE *arch)
{
	ARCHIVEDFILE *zipped_file;
	FILE *arch_file;
	unsigned int i = 0;
	
	if (access(arch->name, R_OK|W_OK) == -1)
	{
		arch_file = fopen(arch->name, "r+");
	}
	else
	{
		arch_file = fopen(arch->name, "w");
	}

	if (arch_file == NULL)
	{
		printf("Permission denied to the archive '%s'\n", arch->name);
		exit(1);
	}

	while (i < arch->files_count)
	{
		zipped_file = arch->files[i];
		fprintf(arch_file, "N%dB%ldF%ldN%sB",
				strlen(zipped_file->name),
				zipped_file->root->length,
				zipped_file->new_size,
				zipped_file->name
		);
		write_bintree(arch_file, zipped_file->root);
		fprintf(arch_file, "F%s", zipped_file->text);
		i++;
	}
	fclose(arch_file);
	return 0;
}
