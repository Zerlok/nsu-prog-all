TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    calendar.cpp \
    date.cpp \
    week.cpp \
    month.cpp \
    calendarformat.cpp

HEADERS += \
    calendar.h \
    date.h \
    week.h \
    month.h \
	calendarformat.h

OTHER_FILES += gtest.cpp \
	../build/task3/calendar_sep_nov.txt \
	../argvparser.h
