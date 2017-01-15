TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt


# OpenGL libs.
QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU

# My libs (logger and shared pointer).
INCLUDEPATH += /home/zerlok/nsu_prog/include
LIBS += -L/home/zerlok/nsu_prog/libs -llogger


#INCLUDEPATH += ../logger/ ../../oop/task11/
#HEADERS += ../logger/logger.hpp ../../oop/task11/sharedpointer.h
#SOURCES += ../logger/logger.cpp

# For debug.
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG -= -O1 -O2 -O3


# Main headers
# (derived modules should be defined in same order as base modules).
# Common classes.
HEADERS += \
    common/color.hpp \
    common/utils.hpp \
    common/event.hpp \
    common/peripherals.hpp \

# Base engine classes.
HEADERS += core/opengls.hpp \
    core/nameable.hpp \
    core/animation.hpp \
    core/component.hpp \
    core/object.hpp

# Textures.
HEADERS += core/texture.hpp \
    textures/squaredwbtexture.hpp \
    textures/imagetexture.hpp

# Shaders.
HEADERS += core/shader.hpp \
    shaders/diffuseshader.hpp \
    shaders/metamorphoseshader.hpp \
    shaders/screwshader.hpp

# Materials.
HEADERS += core/material.hpp \
    materials/diffusematerial.hpp

# Meshes.
HEADERS += core/mesh.hpp \
    meshes/importexport.hpp \
    meshes/cube.hpp \
    meshes/megacube.hpp \
    meshes/cylinder.hpp \
    meshes/sphere.hpp \
    meshes/icosphere.hpp \
    meshes/plane.hpp

# GUI components.
HEADERS += core/gui.hpp \
    gui/guilabel.hpp \
    gui/guiplane.hpp \
    gui/guifps.hpp \
    gui/guiconsole.hpp

# Rest core classes.
HEADERS += \
    core/primitive.hpp \
    core/light.hpp \
    core/camera.hpp \
    core/frame.hpp \
    core/scene.hpp

# Engine.
HEADERS += \
    engine.hpp \
    engineutils.hpp

# Tasks (graphics tasks with custom scenes)
HEADERS += tasks/task.hpp \
    tasks/task04.hpp \
    tasks/task05.hpp \
    tasks/task06.hpp \
    tasks/task07.hpp


# Main sources of modules.
# Common.
SOURCES += \
    common/color.cpp \
    common/utils.cpp \
    common/peripherals.cpp \

# Base engine classes.
SOURCES += core/opengls.cpp \
    core/nameable.cpp \
    core/animation.cpp \
    core/component.cpp \
    core/object.cpp

# Textures.
SOURCES += core/texture.cpp \
    textures/squaredwbtexture.cpp \
    textures/imagetexture.cpp

# Shaders.
SOURCES += core/shader.cpp \
    shaders/metamorphoseshader.cpp \
    shaders/screwshader.cpp \
    shaders/diffuseshader.cpp

# Materials.
SOURCES += core/material.cpp \
    materials/diffusematerial.cpp

# Meshes.
SOURCES += core/mesh.cpp \
    meshes/importexport.cpp \
    meshes/cube.cpp \
    meshes/megacube.cpp \
    meshes/cylinder.cpp \
    meshes/sphere.cpp \
    meshes/icosphere.cpp \
    meshes/plane.cpp

# GUI components.
SOURCES += core/gui.cpp \
    gui/guilabel.cpp \
    gui/guiplane.cpp \
    gui/guifps.cpp \
    gui/guiconsole.cpp

# Rest core classes.
SOURCES += \
    core/primitive.cpp \
    core/light.cpp \
    core/camera.cpp \
    core/frame.cpp \
    core/scene.cpp

# Engine.
SOURCES += engine.cpp

# Tasks (graphics tasks with custom scenes)
SOURCES += tasks/task.cpp \
    tasks/task04.cpp \
    tasks/task05.cpp \
    tasks/task06.cpp \
    tasks/task07.cpp

# Main
SOURCES += main.cpp


# Shaders source files.
DISTFILES += \
    shaders/default.vs \
    shaders/default.gs \
    shaders/default.fs \
    shaders/metamorph.vs \
    shaders/screw.vs \
    shaders/diffuse.vs \
    shaders/diffuse.fs
