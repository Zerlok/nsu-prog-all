TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU


SOURCES += main.cpp \
    scene.cpp \
    camera.cpp \
    mesh.cpp \
    lamp.cpp \
    object.cpp \
    engine.cpp \
    types.cpp \
    material.cpp \
    texture.cpp \
    common/point.cpp

HEADERS += \
    engine.hpp \
    opengls.hpp \
    scene.hpp \
    camera.hpp \
    mesh.hpp \
    lamp.hpp \
    object.hpp \
    types.hpp \
    material.hpp \
    texture.hpp \
    common/point.hpp
