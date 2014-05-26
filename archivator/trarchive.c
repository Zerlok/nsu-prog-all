#include "mod.h"


/* ---------- DEBUG FUNCTIONS ---------- */
#ifdef DEBUG

int run_test(char *file_name)
{
	printf("Test for %s file", file_name);
	return 0;
}

#endif


/* ---------- ACCESSORY FUNCTIONS ---------- */

int read_or_create_an_archive(char *arch_name, ARCHIVE *archive)
/*
Read the archive information to ARCHIVE structure, if archive exist.
Otherwise create the archive struct with basic information.

Input:
	char *arch_name - the name of file
	ARCHIVE *arch - the indicator to archive struct.

Output:
	Return 0 if everything is OK, else error code.
*/
{
	/* Is it an archive file */
	if (is_an_archive(arch_name))
	{
		printf("The file '%s' is not an archive of %s program.\n", arch_name, ARC_NAME);
		return 1;
	}

	FILE *archive_file;
	ARCHIVEDFILE *zipped_file = NULL;
	int file_name_size = 0;
	unsigned long int bin_tree_size = 0, file_text_size = 0, file_normal_size = 0;

	/* Archive init */
	archive->name = (char*)calloc(strlen(arch_name) + 1, sizeof(char));
	archive->files = (ARCHIVEDFILE**)calloc(0, sizeof(ARCHIVEDFILE));
	archive->files_count = 0;
	strcpy(archive->name, arch_name);

	/* Read or create archive file */
	if ((archive_file = fopen(arch_name, "r+")) == NULL)
	{
		/* Create it */
		if ((archive_file = fopen(arch_name, "w")) == NULL)
		{
			printf("Permission denied to the archive '%s'\n", arch_name);
			return 2;
		}
		fclose(archive_file);

		printf("New archive file '%s' created.\n", archive->name);

		return 0;
	}

	/* Read archive file */
	while (fscanf(archive_file, "N%dB%ldF%ld|%ldN",
				&file_name_size,
				&bin_tree_size,
				&file_text_size,
				&file_normal_size
			) != EOF)
	{
		zipped_file = (ARCHIVEDFILE*)malloc(sizeof(ARCHIVEDFILE));
		zipped_file->old_size = file_normal_size;

		/* Read archived file name */
		zipped_file->name = (char*)calloc(file_name_size, sizeof(char));
		fread(zipped_file->name, file_name_size, sizeof(char), archive_file);

		/* Read & build bintree */
		zipped_file->list = NULL;
		if (bin_tree_size > 0)
		{
			zipped_file->root = (BINTREE*)malloc(sizeof(BINTREE));
			build_bintree_from_file(archive_file, zipped_file->root, bin_tree_size, "");
			count_bintree_codes(zipped_file->root, "", 0);
		}
		else
		{
			zipped_file->root = NULL;
		}

		/* Skip archived text */
		zipped_file->start_byte = ftell(archive_file);
		zipped_file->new_size = file_text_size;
		fseek(archive_file, file_text_size, SEEK_CUR);

		archive->files_count += 1;
		archive->files = (ARCHIVEDFILE**)realloc(archive->files, archive->files_count);
		archive->files[archive->files_count - 1] = zipped_file;
	}

	fclose(archive_file);

	printf("Archive file '%s' was read.\n", archive->name);
	return 0;
}


/* ---------- ARCHIVE FUNCTIONS ---------- */


int add_to_archive(char *file_name, ARCHIVE *archive)
/*
Encodes file with haffman algorithm and writes the result to an archive.

Input:
	char *file_name - the name of file.
	ARCHIVE *archive - the pointer to an archive structure.

Output:
	int - error code (everything is ok if zero).
*/
{
	ARCHIVEDFILE *zipped_file;
	FILE *file, *archive_file;
	char buffer[128] = {};
	unsigned long int bin_tree_size, new_size = 0;
	unsigned char chr;
	long int new_size_byte;
	int i = 0;

	/* Check this file in archive */
	if (is_in_archive(file_name, archive) > -1)
	{
		printf("The file '%s' is already added to '%s' archive!\n", file_name, archive->name);
		return 0;
	}

	/* Open file to read */
	if ((file = fopen(file_name, "r")) == NULL)
	{
		printf("Permission denied to the file '%s'\n", file_name);
		return 1;
	}

	/* Open archive file to append */
	if ((archive_file = fopen(archive->name, "r+")) == NULL)
	{
		return 2;
	}

	/* Encode the file (Build bintree and count size of file) */
	zipped_file = encode_file(file);

	/* Get bin_tree depth */
	if (zipped_file->root != NULL)
	{
		bin_tree_size = zipped_file->root->length;
	}
	else
	{
		bin_tree_size = 0;
	}

//	print_list(zipped_file->list);

	/* Write header */
	fprintf(archive_file, "N%dB%ldF", strlen(file_name), bin_tree_size);
	new_size_byte = ftell(archive_file);
	fprintf(archive_file, "0000000000|%ldN%s", zipped_file->old_size, file_name);
	write_bintree_to_file(archive_file, zipped_file->root);

	/* Write zipped file */
	fseek(file, 0, SEEK_SET); // Start read the file again.
	fseek(archive_file, 0, SEEK_END); // Go to the end of archive file.
	while (fread(&chr, sizeof(chr), 1, file))
	{
		if (strlen(buffer) < 8)
		{
			strcat(buffer, get_encoded(zipped_file->list, chr));
		}

		/* While first 8 bits are full */
		while (strlen(buffer) >= 8)
		{
			/* Write as letter */
			fprintf(archive_file, "%c", get_as_one_char(buffer));
			new_size++;

			/*
			Say hello to bugs there:
			1) If strle(buffer) > 120 -> memmove will copy buffer+8 to buffer,
			but last 8 cells will not copy they still will be not \0!
			*/

			/* Shift buffer */
			memmove(buffer, buffer+8, 120);
		}
	}

	/* If buffer is not empty */
	if ((i = strlen(buffer)) > 0)
	{
		/* Fill it with '0' value */
		while (i < 8)
		{
			buffer[i] = '0';
			i++;
		}

		/* Write last letter */
		fprintf(archive_file, "%c", get_as_one_char(buffer));
		new_size++;
	}
	fclose(file);

	/* Write zipped size */
	fseek(archive_file, new_size_byte + (10 - get_nums(new_size)), SEEK_SET);
	fprintf(archive_file, "%ld", new_size);

	fclose(archive_file);

	/* Appending to archive structure */
	zipped_file->name = (char*)calloc(strlen(file_name), sizeof(char));
	strcpy(zipped_file->name, file_name);
	zipped_file->new_size = new_size;

	archive->files_count += 1;
	archive->files = (ARCHIVEDFILE**)realloc(archive->files, archive->files_count);
	archive->files[archive->files_count - 1] = zipped_file;

	return 0;
}


int extract_file_from_archive(char *file_name, ARCHIVE *archive)
/*
Decodes file with haffman algorithm and writes the result to an file.

Input:
	char *file_name - the name of file.
	ARCHIVE *archive - the pointer to an archive structure.

Output:
	int - error code (everything is ok if zero).
*/
{
	FILE *file, *archive_file;
	int file_num = is_in_archive(file_name, archive);

	/* Check this file in archive */
	if (file_num < 0)
	{
		return 3;
	}

	/* Create extracted file */
	if ((file = fopen(file_name, "w")) == NULL)
	{
		return 2;
	}

	/* Open to read archive file */
	if ((archive_file = fopen(archive->name, "r")) == NULL)
	{
		return 1;
	}

	/* Unzip the file */
	decode_file(file, archive_file, archive->files[file_num]);

	fclose(file);
	fclose(archive_file);

	return 0;
}


int show_archived_files(ARCHIVE *archive)
/*
Shows the archived files.

Input:
	ARCHIVE *archive - the pointer to the archive.
*/
{
	float zip_rate;
	int i = 0;
	ARCHIVEDFILE *zipped_file;

	printf("Next files are in '%s' archive:\n", archive->name);
	while (i < archive->files_count)
	{
		zipped_file = archive->files[i];
		if (zipped_file->old_size != 0)
		{
			zip_rate = (float)zipped_file->new_size / (float)zipped_file->old_size;
		}
		else
		{
			zip_rate = 1.0;
		}
		printf("\t%s    zip rate: %d%% (%ld, %ld)\n",
			   zipped_file->name,
			   (int)((1 - zip_rate) * 100),
			   zipped_file->new_size,
			   zipped_file->old_size
		);

		i++;
	}
	printf("\n");

	return 0;
}
