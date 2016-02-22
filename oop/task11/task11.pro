TASKNAME = SharedPointer

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11

HEADERS += \
    sharedpointer.h

SOURCES += \
	main.cpp

OTHER_FILES += \
	gtest.cpp

