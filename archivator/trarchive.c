#include "mod.h"

//#ifndef __COMMON_H__
//#define __COMMON_H__

//int check_mem(void *pointer, const char *func_name)
//{
//	if (pointer == NULL)
//	{
//		printf("Cannot assign the memory at %s function!\n", func_name);
//		exit(10);
//	}
//	return 0;
//}

//#endif


/* ---------- DEBUG FUNCTIONS ---------- */

int run_test(char *file_name, char *archive_name)
{
	ARCHIVE *archive = (ARCHIVE*)malloc(sizeof(ARCHIVE));
	check_mem(archive, __func__);

	create_an_archive(archive_name, archive);

	add_to_archive(file_name, archive);

	print_bintree(archive->files[0]->root, "");

	return 0;
}


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
	{
		/* TODO: do not skip the '.trarlololo'. '.trar' only! */
		return 1;
	}
	return 0;
}


int is_in_archive(char *file_name, ARCHIVE *archive)
/*
If file is in archive file returns it's number.
Otherwise returns -1.

Input:
	char *file_name - the name of file.
*/
{
	int i = 0;

	/* Check this file in archive */
	while (i < archive->files_count)
	{
		if (!strcmp(file_name, archive->files[i]->name))
		{
			return i;
		}

		i++;
	}

	return -1;
}


int read_an_archive(char *arch_name, ARCHIVE *archive)
/*
Read the archive information to ARCHIVE structure, if archive exist.

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
		return 2;
	}

	FILE *archive_file;
	ARCHIVEDFILE *zipped_file = NULL;
	int file_name_size = 0;
	unsigned long int bin_tree_size = 0, file_text_size = 0, file_normal_size = 0;

	/* Archive init */
	archive->name = (char*)calloc(strlen(arch_name) + 1, sizeof(char));
	check_mem(archive->name, __func__);

	archive->files = (ARCHIVEDFILE**)calloc(0, sizeof(ARCHIVEDFILE));
	check_mem(archive->files, __func__);

	archive->files_count = 0;
	strcpy(archive->name, arch_name);

	/* Open archive file for reading */
	if ((archive_file = fopen(arch_name, "r")) == NULL)
	{
		return 1;
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
		check_mem(zipped_file, __func__);

		zipped_file->list = NULL;
		zipped_file->original_size = file_normal_size;

		/* Read archived file name */
		zipped_file->name = (char*)calloc(file_name_size, sizeof(char));
		check_mem(zipped_file->name, __func__);

		fread(zipped_file->name, file_name_size, sizeof(char), archive_file);

		/* Read & build bintree */
		if (bin_tree_size > 0)
		{
			zipped_file->root = (BINTREE*)malloc(sizeof(BINTREE));
			check_mem(zipped_file->root, __func__);

			build_bintree_from_file(archive_file, zipped_file->root, bin_tree_size, "");
			count_bintree_codes(zipped_file->root, "", 0);
		}
		else
		{
			zipped_file->root = NULL;
		}

		/* Skip archived text */
		zipped_file->start_byte = ftell(archive_file);
		zipped_file->zipped_size = file_text_size;
		fseek(archive_file, file_text_size, SEEK_CUR);

		archive->files_count += 1;
		archive->files = (ARCHIVEDFILE**)realloc(archive->files, archive->files_count);
		check_mem(archive->files, __func__);

		archive->files[archive->files_count - 1] = zipped_file;
	}

	fclose(archive_file);

//	("Archive file '%s' was read.\n", archive->name);
	return 0;
}


int create_an_archive(char *arch_name, ARCHIVE *archive)
/*
Creates the new archive file and structure with basic information.

Input:
	char *arch_name - the name of file
	ARCHIVE *arch - the indicator to archive struct.

Output:
	Return 0 if everything is OK, else error code.
*/
{
	if (is_an_archive(arch_name))
	{
		return 1;
	}

	FILE *archive_file;

	/* Archive init */
	archive->name = (char*)calloc(strlen(arch_name) + 1, sizeof(char));
	check_mem(archive->name, __func__);

	archive->files = (ARCHIVEDFILE**)calloc(0, sizeof(ARCHIVEDFILE));
	check_mem(archive->files, __func__);

	archive->files_count = 0;
	strcpy(archive->name, arch_name);

	/* Check is archive file unreadable (doesn't exist) */
	if ((archive_file = fopen(arch_name, "r")) == NULL)
	{
		if ((archive_file = fopen(arch_name, "w")) == NULL)
		{
			return 2;
		}

		fclose(archive_file);

		return 0;
	}

	fclose(archive_file);

	return 3;
}


/* ---------- ARCHIVE FUNCTIONS ---------- */


int get_nums(unsigned long int x)
{
	int n = 10;
	unsigned long int k = 1000000000;

	while (n > 0 && (int)(x / k) == 0)
	{
		if (k != 1)
		{
			k /= 10;
		}
		n--;
	}

	if (n < 1)
	{
		n = 1;
	}

	return n;
}


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
	unsigned long int bin_tree_size, zipped_size = 0;
	unsigned char chr;
	char new_chr;
	long int zipped_size_byte, b;
	int i = 0;

	/* Check this file in archive */
	if (is_in_archive(file_name, archive) > -1)
	{
		return 3;
	}

	/* Open file to read */
	if ((file = fopen(file_name, "r")) == NULL)
	{
		return 2;
	}

	/* Open archive file to append */
	if ((archive_file = fopen(archive->name, "r+")) == NULL)
	{
		return 1;
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
	zipped_size_byte = ftell(archive_file);
	fprintf(archive_file, "0000000000|%ldN%s", zipped_file->original_size, file_name);
	write_bintree_to_file(archive_file, zipped_file->root);

	/* Write zipped file */
	fseek(file, 0, SEEK_SET); // Start read the file again.
	fseek(archive_file, 0, SEEK_END); // Go to the end of archive file.
	while (fread(&chr, 1, sizeof(char), file))
	{
		if (strlen(buffer) < 8)
		{
			strcat(buffer, get_encoded(zipped_file->list, chr));
		}

		/* While first 8 bits are full */
		while (strlen(buffer) >= 8)
		{
			/* Write as letter */
			new_chr = get_as_one_char(buffer);
			fprintf(archive_file, "%c", new_chr);
			zipped_size++;

//			b = ftell(file);

//			if ((b > 530) && (b < 560))
//			{
//				printf("%ld: (%03d)'%c' => [%8s] => '%c' | buff: [%20s]\n", b, chr, chr, get_encoded(zipped_file->list, chr), get_as_one_char(buffer), buffer);
//			}

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
		zipped_size++;
	}
	fclose(file);

	/* Write zipped size */
	fseek(archive_file, zipped_size_byte + (10 - get_nums(zipped_size)), SEEK_SET);
	fprintf(archive_file, "%ld", zipped_size);

	fclose(archive_file);

	/* Appending to archive structure */
	zipped_file->name = (char*)calloc(strlen(file_name) + 1, sizeof(char));
	check_mem(zipped_file->name, __func__);

	strcpy(zipped_file->name, file_name);
	zipped_file->zipped_size = zipped_size;

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

	printf("'%s' contains:\n", archive->name);
	while (i < archive->files_count)
	{
		zipped_file = archive->files[i];
		if (zipped_file->original_size != 0)
		{
			zip_rate = (float)zipped_file->zipped_size / (float)zipped_file->original_size;
		}
		else
		{
			zip_rate = 1.0;
		}
		printf("\t%s    zip rate: %d%% (%ld, %ld)\n",
			   zipped_file->name,
			   (int)((1 - zip_rate) * 100),
			   zipped_file->zipped_size,
			   zipped_file->original_size
		);

		i++;
	}
	printf("\n");

	return 0;
}
