# Basic constants.
CC=gcc
#CFLAGS=

CCPP=g++
CPPFLAGS=-std=c++11

BINNAME=result.bin
OBJECT_BINARIES=object.cpp main.cpp

# By tasks.
TASK1_BINARIES=task1/longstring.c task1/recordarray.c task1/main.c
TASK2_BINARIES=task2/class.c task2/shape.c task2/point.c task2/rectangle.c task2/circle.c task2/factory.c task2/main.c


# Longstring and recordarray.
first:
	$(CC) $(TASK1_BINARIES) -o $(BINNAME)


# Factory (Object Oriented C).
second:
	$(CC) $(TASK2_BINARIES) -o $(BINNAME)


# Just a little experiment.
object:
	$(CCPP) $(CPPFLAGS) $(OBJECT_BINARIES) -o $(BINNAME)


clean:
	rm $(BINNAME)


.PHONY:
	clean
