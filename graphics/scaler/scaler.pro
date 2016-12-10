TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


LIBS += -lpng
QMAKE_CXXFLAGS +=\
    -std=c++11 \
    -lpng


SOURCES += main.cpp \
    image.cpp

HEADERS += \
    image.hpp

