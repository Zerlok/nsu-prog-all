#include "main.h"
#include "streams.h"


int create_stream(char *filename, int flags)
{
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


void redirect_stream(int from, int to)
{
	if (from == to)
		return;

	DEBUG_START("Redirecting the stream %d --> %d ...", from, to);

	if (from == -1)
	{
		DEBUG_END("failed (from stream is invalid).");
		return;
	}

	DEBUG_SAY("Duplicating streams ...\n");
	dup2(from, to);
	DEBUG_SAY("duplicated.\n");
	close(to);

	DEBUG_END("done.");
}
