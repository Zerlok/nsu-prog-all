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
    object.cpp \
    engine.cpp \
    material.cpp \
    texture.cpp \
    common/color.cpp \
    component.cpp \
    meshes/cube.cpp \
    meshes/strangecube.cpp \
    shader.cpp \
    shaders/metamorphose_shader.cpp \
    meshes/megacube.cpp \
    meshes/cylinder.cpp \
    shaders/screwshader.cpp \
    light.cpp \
    lamps/lamp.cpp \
    gui.cpp \
    gui/guifps.cpp \
    gui/guilabel.cpp \
    gui/guiplane.cpp \
    materials/diffusematerial.cpp \
    common/utils.cpp

HEADERS += \
    engine.hpp \
    opengls.hpp \
    scene.hpp \
    camera.hpp \
    mesh.hpp \
    object.hpp \
    material.hpp \
    texture.hpp \
    common/color.hpp \
    common/utils.h \
    component.hpp \
    meshes/cube.hpp \
    meshes/strangecube.hpp \
    shader.hpp \
    shaders/metamorphose_shader.h \
    meshes/megacube.hpp \
    meshes/cylinder.hpp \
    shaders/screwshader.hpp \
    light.hpp \
    lamps/lamp.hpp \
    gui.hpp \
    gui/guilabel.hpp \
    gui/guifps.hpp \
    gui/guiplane.hpp \
    materials/diffusematerial.hpp
