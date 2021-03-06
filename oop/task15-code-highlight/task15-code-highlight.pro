TASKNAME = Code Highlight

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -lpthread -lgtest

LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest


SOURCES += main.cpp \
	decorators.cpp \
    stringutils.cpp \
	component.cpp

HEADERS += \
    decorators.h \
    stringutils.h \
    component.h

OTHER_FILES += \
	gtest.cpp \
	toparse.cpp
