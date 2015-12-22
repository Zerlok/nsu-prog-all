TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    imagepng.cpp \
    utils.cpp

HEADERS += \
    imagepng.h \
    utils.h

LIBS += -lpng
QMAKE_CFLAGS +=-lpng
INCLUDEPATH += /usr/include/libpng12
