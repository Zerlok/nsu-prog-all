TASKNAME = Lifegame (plants, herbivorous, predators).

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
    action.cpp \
    plant.cpp \
    herbivorous.cpp \
    predator.cpp

HEADERS += console.h \
	point.h \
    lifeobject.h \
    populationmap.h \
	populationmapview.h \
	gamelogic.h \
    action.h \
    plant.h \
    herbivorous.h \
    predator.h \
    config.h

OTHER_FILES += gtest.cpp

LIBS += -lncurses
QMAKE_CFLAGS += -lncurses
QMAKE_CFLAGS_RELEASE += -O3
