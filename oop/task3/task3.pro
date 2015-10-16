TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    calendar.cpp \
    date.cpp \
    week.cpp \
    month.cpp \
    calendarformat.cpp \
    calendarparser.cpp

HEADERS += \
    calendar.h \
    date.h \
    week.h \
    month.h \
    calendarformat.h \
    calendarparser.h

OTHER_FILES += gtest.cpp \
    ../build/task3/calendar_sep_nov.txt
