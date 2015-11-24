TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	point.cpp \
    lifeobject.cpp \
	populationmap.cpp \
	populationmapview.cpp \
	gamelogic.cpp

HEADERS += \
	point.h \
    lifeobject.h \
    populationmap.h \
	populationmapview.h \
	gamelogic.h

OTHER_FILES += gtest.cpp
