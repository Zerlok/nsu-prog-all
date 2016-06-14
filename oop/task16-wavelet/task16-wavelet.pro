TASKNAME = Wavelet transformation (refactoring from C to C++)

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=gnu++11 -lpthread -lgtest

LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest


SOURCES += \
	main.cpp \
	wtr.cpp \
    haartransformation.cpp

HEADERS += \
	wtr.h \
    transformation.h \
    haartransformation.h

OTHER_FILES += \
	gtest.cpp
