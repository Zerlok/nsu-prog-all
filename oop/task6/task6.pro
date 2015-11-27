TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += console.c \
	main.cpp \
	point.cpp \
    lifeobject.cpp \
	populationmap.cpp \
	populationmapview.cpp \
	gamelogic.cpp \

HEADERS += console.h \
	point.h \
    lifeobject.h \
    populationmap.h \
	populationmapview.h \
	gamelogic.h \

OTHER_FILES += gtest.cpp


LIBS += -lncurses
QMAKE_CFLAGS += -lncurses

