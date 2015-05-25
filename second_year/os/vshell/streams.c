#include "main.h"
#include "streams.h"


int create_stream(char *filename, int flags)
{
	if (filename == NULL)
	{
		DEBUG_SAY("NULLING");
		return -2;
	}

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
	DEBUG_START("Redirecting the stream %d -> %d ...", old_stream, new_stream);

	if (new_stream == -1)
	{
		DEBUG_END("failed (new stream is invalid).");
		return;
	}

	DEBUG_SAY("Duplicating streams %d to %d ...\n", new_stream, old_stream);
	dup2(new_stream, old_stream);
	DEBUG_SAY("duplicated.\n");
	close(new_stream);

	DEBUG_END("done.");
}
