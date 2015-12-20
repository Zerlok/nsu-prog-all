TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    imagepng.cpp


LIBS += -lpng
QMAKE_CFLAGS+=-lpng
INCLUDEPATH += /usr/include/libpng12

HEADERS += \
    imagepng.h
