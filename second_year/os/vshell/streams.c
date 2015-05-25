#include "main.h"
#include "streams.h"


int create_stream(char *filename, int flags)
{
	if (filename == NULL)
		return -2;

	DEBUG_START("Creating the new stream ...");

	int new_stream = open(filename, flags, 0644);

	if (new_stream == -1)
	{
		perror(strerror(errno));
		DEBUG_END("failed (cannot create a stream for %s file).", filename);
		return -1;
	}

	DEBUG_END("done.");
	return new_stream;
}


void redirect_stream(int old_stream, int new_stream)
{
	if (new_stream == -2)
		return;

	DEBUG_START("Redirecting the stream ...");

	if (new_stream == -1)
	{
		perror(strerror(errno));
		DEBUG_END("failed (new stream is invalid).");
		return;
	}
	else if ((new_stream == STDIN_FILENO)
			 || (new_stream == STDOUT_FILENO)
			 || (new_stream == STDERR_FILENO))
	{
		DEBUG_END("failed (redirect to std stream '%d').", new_stream);
		return;
	}

	dup2(new_stream, old_stream);
	close(new_stream);

	DEBUG_END("done.");
}
