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


# Main modules.
# (custom modules should be defined in same order).
HEADERS += \
    core/opengls.hpp \
    core/component.hpp \
    core/object.hpp \
    core/shader.hpp \
    core/texture.hpp \
    core/material.hpp \
    core/mesh.hpp \
    core/primitive.hpp \
    core/light.hpp \
    core/camera.hpp \
    core/frame.hpp \
    core/scene.hpp \
    core/gui.hpp \
    core/animation.hpp \
    engine.hpp

# Custom shaders.
HEADERS += \
    shaders/diffuseshader.hpp \
    shaders/metamorphoseshader.hpp \
    shaders/screwshader.hpp

# Custom materials.
HEADERS += \
    materials/diffusematerial.hpp

# Custom meshes.
HEADERS += \
    meshes/cube.hpp \
    meshes/megacube.hpp \
    meshes/cylinder.hpp \
    meshes/sphere.hpp \
    meshes/plane.hpp

# Custom GUI components.
HEADERS += \
    gui/guilabel.hpp \
    gui/guiplane.hpp \
    gui/guifps.hpp \
    gui/guiconsole.hpp

# Other.
HEADERS += \
    common/color.hpp \
    common/utils.hpp \
    engineutils.hpp


# Main sources of modules.
SOURCES += \
    core/component.cpp \
    core/object.cpp \
    core/shader.cpp \
    core/texture.cpp \
    core/material.cpp \
    core/mesh.cpp \
    core/primitive.cpp \
    core/light.cpp \
    core/camera.cpp \
    core/frame.cpp \
    core/scene.cpp \
    core/gui.cpp \
    core/animation.cpp \
    engine.cpp \
    main.cpp

# Custom shaders.
SOURCES += \
    shaders/metamorphoseshader.cpp \
    shaders/screwshader.cpp \
    shaders/diffuseshader.cpp

# Custom materials.
SOURCES += \
    materials/diffusematerial.cpp

# Custom meshes.
SOURCES += \
    meshes/cube.cpp \
    meshes/megacube.cpp \
    meshes/cylinder.cpp \
    meshes/sphere.cpp \
    meshes/plane.cpp

# Custom GUI components.
SOURCES += \
    gui/guilabel.cpp \
    gui/guiplane.cpp \
    gui/guifps.cpp \
    gui/guiconsole.cpp

# Other.
SOURCES += \
    common/color.cpp \
    common/utils.cpp

DISTFILES += \
    shaders/default.vs \
    shaders/default.gs \
    shaders/default.fs \
    shaders/metamorph.vs \
    shaders/screw.vs \
    shaders/diffuse.vs \
    shaders/diffuse.fs
