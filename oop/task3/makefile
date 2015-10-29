# Basic constants.
CCPP=g++
CPPFLAGS=-std=c++11

GTESTFLAGS=-lgtest -lpthread
GTESTFILE=gtest.cpp
GTESTBINNAME=test-calendr

SOURCES=date.cpp week.cpp month.cpp calendar.cpp calendarformat.cpp
MAINFILE=main.cpp
BINNAME=calendr


all: test app


test:
	$(CCPP) $(CPPFLAGS) $(SOURCES) $(GTESTFILE) -o $(GTESTBINNAME) $(GTESTFLAGS)


app:
	$(CCPP) $(CPPFLAGS) $(SOURCES) $(MAINFILE) -o $(BINNAME)


clean:
	rm $(BINNAME)
	rm $(GTESTBINNAME)


.PHONY:
	clean
