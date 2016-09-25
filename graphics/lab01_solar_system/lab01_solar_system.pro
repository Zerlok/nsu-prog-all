TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGLU -lGEW
LIBS += -lglut -lGL -lGLU -lGLEW
