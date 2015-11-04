TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	graph.cpp

HEADERS += graph.h \
    treebuilder.h

OTHER_FILES += gtest.cpp
