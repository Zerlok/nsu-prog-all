TASKNAME = FilterIterator

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp

HEADERS += filteriterator.h

OTHER_FILES += gtest.cpp
