TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


# OpenGL libs.
QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU


# For debug.
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG -= -O1 -O2 -O3


# My libs (logger and shared pointer).
INCLUDEPATH += /home/zerlok/nsu_prog/include
LIBS += -L/home/zerlok/nsu_prog/libs -llogger


# Main modules.
# (custom modules should be in same order).
HEADERS += \
    opengls.hpp \
    component.hpp \
    object.hpp \
    shader.hpp \
    texture.hpp \
    material.hpp \
    mesh.hpp \
    light.hpp \
    camera.hpp \
    scene.hpp \
    gui.hpp \
    engine.hpp \

# Custom shaders.
HEADERS += \
    shaders/metamorphoseshader.hpp \
    shaders/screwshader.hpp \
    shaders/diffuseshader.hpp

# Custom materials.
HEADERS += \
    materials/diffusematerial.hpp

# Custom meshes.
HEADERS += \
    meshes/cube.hpp \
    meshes/strangecube.hpp \
    meshes/megacube.hpp \
    meshes/cylinder.hpp

# Custom lamps.
HEADERS += \
    lamps/lamp.hpp

# Custom GUI components.
HEADERS += \
    gui/guilabel.hpp \
    gui/guifps.hpp \
    gui/guiplane.hpp

# Other.
HEADERS += \
    common/color.hpp \
    common/utils.h


# Main sources of modules.
SOURCES += \
    component.cpp \
    object.cpp \
    shader.cpp \
    texture.cpp \
    material.cpp \
    mesh.cpp \
    light.cpp \
    camera.cpp \
    scene.cpp \
    gui.cpp \
    engine.cpp \
    main.cpp \

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
    meshes/strangecube.cpp \
    meshes/megacube.cpp \
    meshes/cylinder.cpp

# Custom lamps.
SOURCES += \
    lamps/lamp.cpp

# Custom GUI components.
SOURCES += \
    gui/guifps.cpp \
    gui/guilabel.cpp \
    gui/guiplane.cpp

# Other.
SOURCES += \
    common/color.cpp \
    common/utils.cpp
