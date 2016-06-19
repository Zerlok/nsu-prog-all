TASKNAME = Wavelet transformation (refactoring from C to C++)

TEMPLATE = app
CONFIG += console gnu++11 release
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=gnu++11


SOURCES += \
	wtr.cpp \
	haartransformation.cpp

debug {
	QMAKE_CXXFLAGS += -lpthread -lgtest
	LIBS += -lpthread -lgtest
	INCLUDEPATH += /usr/include/gtest
	SOURCES += gtest.cpp
	message("Google Unit Tests enabled!")
}

release {
	SOURCES += main.cpp
	message("Release build set!")
}


HEADERS += \
	wtr.h \
    transformation.h \
    haartransformation.h

