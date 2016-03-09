TASKNAME = Big Vector (with file buffer)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11 -lpthread -lgtest

SOURCES += main.cpp

HEADERS += \
    bigvector.h \
    serdeser.h

LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest

DISTFILES += \
	../build/task13/data.ser
