TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU

INCLUDEPATH += /home/zerlok/nsu_prog/include
LIBS += -L/home/zerlok/nsu_prog/libs -llogger


SOURCES += main.cpp \
    scene.cpp \
    camera.cpp \
    mesh.cpp \
    lamp.cpp \
    object.cpp \
    engine.cpp \
    material.cpp \
    texture.cpp \
    common/point.cpp \
    common/color.cpp \
    component.cpp \
    meshes/cube.cpp \
    meshes/strangecube.cpp \
    shader.cpp \
    shaders/metamorphose_shader.cpp

HEADERS += \
    engine.hpp \
    opengls.hpp \
    scene.hpp \
    camera.hpp \
    mesh.hpp \
    lamp.hpp \
    object.hpp \
    material.hpp \
    texture.hpp \
    common/point.hpp \
    common/color.hpp \
    common/utils.h \
    component.hpp \
    meshes/cube.hpp \
    meshes/strangecube.hpp \
    shader.hpp \
    shaders/metamorphose_shader.h
