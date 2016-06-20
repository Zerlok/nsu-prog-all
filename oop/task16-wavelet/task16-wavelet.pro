TASKNAME = Wavelet transformation (refactoring from C to C++)

TEMPLATE = app
CONFIG += console gnu++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=gnu++11


HEADERS += \
	transformation.h \
	transformators.h \
	daub4.h \
	haar.h \
    utils.h

SOURCES += gtest.cpp main.cpp

equals(DEFINES, _DEBUG_)
{
	QMAKE_CXXFLAGS += -lpthread -lgtest
	LIBS += -lpthread -lgtest
	INCLUDEPATH += /usr/include/gtest
}
