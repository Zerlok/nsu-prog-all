TASKNAME = Object Pool

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11 -lpthread -lgtest

SOURCES += gtest.cpp

HEADERS += \
    pool.h

LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest
