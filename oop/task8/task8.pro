TASKNAME = Image auto-rotation

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    imagepng.cpp \
    utils.cpp \
	affinetransformation.cpp \
    imageleapscounter.cpp


HEADERS += \
    imagepng.h \
    utils.h \
    affinetransformation.h \
    imageleapscounter.h \
    histogram.h


OTHER_FILES += gtest.cpp


LIBS += -lpng
QMAKE_CFLAGS +=-lpng
INCLUDEPATH += /usr/include/libpng12
