# Basic constants.
CC=gcc
#CFLAGS=

CCPP=g++
CPPFLAGS=-std=c++11

BINNAME=result.bin
OBJECT_BINARIES=samples/object.cpp samples/main.cpp

# By tasks.
TASK1_SOURCES=task1/longstring.c task1/recordarray.c task1/main.c
TASK2_SOURCES=task2/class.c task2/shape.c task2/point.c task2/rectangle.c task2/circle.c task2/factory.c task2/main.c
TASK3_SOURCES=task3/date.cpp task3/week.cpp task3/month.cpp task3/calendar.cpp task3/calendarformat.cpp task3/main.cpp
TASK4_SOURCES=task4/graph.cpp task4/main.cpp


# Longstring and recordarray.
first:
	$(CC) $(TASK1_SOURCES) -o $(BINNAME)


# Factory (Object Oriented C).
second:
	$(CC) $(TASK2_SOURCES) -o $(BINNAME)


# A simple calendar on c++
third:
	$(CCPP) $(CPPFLAGS) $(TASK3_SOURCES) -o $(BINNAME)


# Tree building algorythm on c++
fourth:
	$(CCPP) $(CPPFLAGS) $(TASK4_SOURCES) -o $(BINNAME)


# Just a little experiment.
object:
	$(CCPP) $(CPPFLAGS) $(OBJECT_BINARIES) -o $(BINNAME)


clean:
	rm $(BINNAME)


.PHONY:
	clean
