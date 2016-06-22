TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11

LIBS += -lopencv_core -lopencv_highgui -lopencv_photo -lpthread -lgtest
INCLUDEPATH += /usr/local/lib /usr/include/gtest

SOURCES += \
	main.cpp \
	gtest.cpp

HEADERS += \
	cvtransformation.h \
	../task16-wavelet/transformation.h \
	../task16-wavelet/transformators.h \
	../task16-wavelet/haar.h \
	../task16-wavelet/daub4.h \
	../task16-wavelet/utils.h
