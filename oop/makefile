CC=g++
CFLAGS=-std=c++11
OBJECT_BINARIES=object.cpp main.cpp
TASK1_BINARIES=task1/longstring.c task1/recordarray.c task1/main.c
BINNAME=result.bin


first:
	gcc $(TASK1_BINARIES) -o $(BINNAME)


object:
	$(CC) $(CFLAGS) $(OBJECT_BINARIES) -o $(BINNAME)


clean:
	rm $(BINNAME)


.PHONY:
	clean
