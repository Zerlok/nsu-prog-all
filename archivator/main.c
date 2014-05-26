#include "mod.h"


int main(int argc, char *argv[])
{
	ARCHIVE *archive = (ARCHIVE*)malloc(sizeof(ARCHIVE));
	int code = HELP_CODE, indx = 0;

	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		code -= indx;

		if (code < HELP_CODE)
		{
			read_or_create_an_archive(argv[2], archive);
		}

		switch (code)
		{
			case APPEND_CODE:
			{
				add_to_archive(argv[indx], archive);
				break;
			}
			case EXTRACT_CODE:
				extract_file_from_archive(argv[indx], archive);
				break;
			case LIST_CODE:
				show_archived_files(archive);
				break;
#ifdef DEBUG
			case TESTMODE_CODE:
				run_test(argv[indx]);
				break;
#endif
			case HELP_CODE:
				print_doc();
				break;
			default:
			{
				if (code > ERROR_CODE)
				{
					print_err(code);
				}
				else
				{
					printf("Program stopped with unknown code: %d\n", code);
				}
				return 1;
			}
		}
	}
	else
	{
		print_doc();
	}
	
	return 0;
}
