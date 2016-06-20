TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11


LIBS += -lopencv_core -lopencv_highgui -lopencv_photo
INCLUDEPATH += /usr/local/lib

QMAKE_CXXFLAGS += -lpthread -lgtest
LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest
SOURCES += gtest.cpp main.cpp

HEADERS += \
	../task16-wavelet/transformation.h \
	../task16-wavelet/transformators.h \
	../task16-wavelet/haar.h \
	../task16-wavelet/daub4.h
