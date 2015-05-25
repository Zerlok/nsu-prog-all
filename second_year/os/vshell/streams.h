#ifndef __STREAMS_H__
#define __STREAMS_H__


#define INPUT_STREAM_FLAGS (O_RDONLY)
#define OUTPUT_STREAM_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define APPEND_STREAM_FLAGS (O_WRONLY | O_CREAT | O_APPEND)
#define ERROR_STREAM_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)


int create_stream(char *filename, int flags);
void redirect_stream(int from, int to);


// __STREAMS_H__
#endif
