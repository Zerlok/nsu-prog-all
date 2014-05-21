#include "mod.h"


/* ---------- DEBUG FUNCTIONS ---------- */


int run_test(char *file_name)
{
	ARCHIVE *archive = (ARCHIVE*)malloc(sizeof(ARCHIVE));
	ARCHIVEDFILE *zipped_file, *encoded_file;
	FILE *file;

	if ((file = fopen(file_name, "rb")) == NULL)
	{
		printf("cannot open the file!\n");
		return 1;
	}

	encoded_file = encode_file(file);
	print_bintree(encoded_file->root, "");
	printf("\nEncoded:\n%s\n\n", encoded_file->text);
	fclose(file);

	read_or_create_an_archive("test/my_archive.trar", archive);
	zipped_file = archive->files[archive->files_count - 1];
	print_bintree(zipped_file->root, "");
	printf("Encoded '%s':\n%s\n\n", zipped_file->name, zipped_file->text);
	return 0;
}

//{
//	FILE *file;
//	ARCHIVEDFILE *zipped_file;

//	if ((file = fopen(file_name, "rb")) == NULL)
//	{
//		printf("cannot open the file!\n");
//		return 1;
//	}

//	zipped_file = encode_file(file);
//	printf("\nEncoded:\n%s\n\n", zipped_file->text);
//	fclose(file);

//	return 0;
//}


/* ---------- ACCESSORY FUNCTIONS ---------- */


int is_an_archive(char *file_name)
/*
If file is an archive file returns 0.
Otherwise returns 1.

Input:
	char *file_name - the name of file.
*/
{
	if (!strstr(file_name, ARC_FILE_TAG)) // If not archive file
		/* TODO: do not skip the '.trarlololo'. '.trar' only! */
	{
		return 1;
	}
	return 0;
}


unsigned int is_in_archive(char *file_name, ARCHIVE *archive)
{
	unsigned int i = 0;

	/* Check this file in archive */
	while (i < archive->files_count)
	{
		if (!strcmp(file_name, archive->files[i]->name))
		{
			printf("The file '%s' is in '%s' archive.\n", file_name, archive->name);
			return i;
		}

		i++;
	}

	return archive->files_count + 1;
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
	if (is_an_archive(arch_name))
	{
		printf("The file '%s' is not an archive of %s program.\n", arch_name, ARC_NAME);
		exit(1);
	}

	/* Archive init */
	FILE *arch_file;
	ARCHIVEDFILE *zipped_file = NULL;
	char chr = 0;
	int file_name_size = 0;
	unsigned long int bin_tree_size = 0, file_text_size = 0;
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

	/* Read archive file */
	while (fread(&chr, sizeof(chr), 1, arch_file))
	{
		zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));
		if (chr == 'N')
		{
			if (fscanf(arch_file, "%dB%ldF%ld|%ldN", &file_name_size, &bin_tree_size, &file_text_size, &(zipped_file->old_size)) == EOF)
			{
				printf("Archive is damaged!\n");
				exit(1);
			}

			/* Read archived file name */
			zipped_file->name = (char*)calloc(file_name_size, sizeof(char));
			fread(zipped_file->name, file_name_size, 1, arch_file);

			/* Read & build bintree */
			if (bin_tree_size > 0)
			{
				zipped_file->root = (BINTREE*)malloc(sizeof(BINTREE));
				build_bintree_from_file(arch_file, zipped_file->root, bin_tree_size, "");
			}
			else
			{
				zipped_file->root = NULL;
			}


			/* Read archived text */
			zipped_file->text = (char*)calloc(file_text_size, sizeof(char));
			if (file_text_size > 0)
			{
				zipped_file->new_size = file_text_size;
				fread(zipped_file->text, file_text_size, 1, arch_file);
			}
		}
		count_bintree_codes(zipped_file->root, "", 0);
		arch->files_count += 1;
		arch->files = (ARCHIVEDFILE**)realloc(arch->files, arch->files_count);
		arch->files[arch->files_count - 1] = zipped_file;
	}

	fclose(arch_file);

	/* IF ARCHIVE EXIST: */
	printf("Archive file '%s' is already exist.\n", arch->name);
	return 0;
}


int write_an_archive_to_file(ARCHIVE *archive)
{
	ARCHIVEDFILE *zipped_file;
	FILE *arch_file;
	unsigned int i = 0;

	if (access(archive->name, R_OK|W_OK) == -1)
	{
		arch_file = fopen(archive->name, "r+");
	}
	else
	/* Try to create new file */
	{
		arch_file = fopen(archive->name, "w");
	}

	if (arch_file == NULL)
	{
		printf("Permission denied to the archive '%s'\n", archive->name);
		exit(1);
	}

	/* Write every zipped file to archive file */
	while (i < archive->files_count)
	{
		zipped_file = archive->files[i];

		if (zipped_file->new_size == 0 && zipped_file->old_size == 0)
		{
			printf("\nThe size of new file is zero!\n");
			fprintf(arch_file, "N%dB0F0|0N%s",
					strlen(zipped_file->name),
					zipped_file->name
			);
		}
		else
		{
			/* Write header */
			fprintf(arch_file, "N%dB%ldF%ld|%ldN%s",
					strlen(zipped_file->name),
					zipped_file->root->length,
					zipped_file->new_size,
					zipped_file->old_size,
					zipped_file->name
			);

			/* Write bintree & text */
			write_bintree_to_file(arch_file, zipped_file->root);
			fprintf(arch_file, "%s", zipped_file->text);
		}

		i++;
	}
	fclose(arch_file);
	return 0;
}


/* ---------- ARCHIVE FUNCTIONS ---------- */


int add_to_archive(char *file_name, ARCHIVE *archive)
{
	printf("Adding to '%s' archive\n", archive->name);
	ARCHIVEDFILE *zipped_file;
	FILE *file;

	/* Check this file in archive */
	if (is_in_archive(file_name, archive) < archive->files_count)
	{
		printf("The file '%s' is already added to '%s' archive!\n", file_name, archive->name);
		return 0;
	}

	/* Is file exist or readable */
	if ((file = fopen(file_name, "r")) == NULL)
	{
		printf("Permission denied to the file '%s'\n", file_name);
		return 1;
	}
	zipped_file = encode_file(file);
	strcpy(zipped_file->name, file_name);

	/* Appending to archive structure */
	archive->files_count += 1;
	archive->files = (ARCHIVEDFILE**)realloc(archive->files, archive->files_count);
	archive->files[archive->files_count - 1] = zipped_file;

	fclose(file);
	return 0;
}


int extract_file_from_archive(char *file_name, ARCHIVE *archive)
{
	FILE *file;
	unsigned int file_num = is_in_archive(file_name, archive);

	/* Check this file in archive */
	if (file_num > archive->files_count)
	{
		return 1;
	}

	if ((file = fopen(file_name, "w")) == NULL)
	{
		return 2;
	}

	decode_file(file, archive->files[file_num]);

	fclose(file);

	return 0;
}


int show_archived_files(ARCHIVE *archive)
{
	unsigned int i = 0;
	ARCHIVEDFILE *zipped_file;

	printf("\nNext files are in '%s' archive:\n", archive->name);
	while (i < archive->files_count)
	{
		zipped_file = archive->files[i];
		printf("\t%s (zipped %ld, unzipped %ld) bytes\n", zipped_file->name, zipped_file->new_size, zipped_file->old_size);

		i++;
	}
	printf("\n");

	return 0;
}
