TASKNAME = SharedPointer

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11

HEADERS += \
    sharedpointer.h

SOURCES += \
	gtest.cpp


LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest
