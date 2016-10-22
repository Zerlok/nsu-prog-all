TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# OpenGL libs.
QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU


# My libs (logger and shared pointer).
#INCLUDEPATH += /home/zerlok/nsu_prog/include
#LIBS += -L/home/zerlok/nsu_prog/libs -llogger


# For Debug only.
#QMAKE_CXXFLAGS += -O0
#QMAKE_CXXFLAGS -= -O1
#QMAKE_CXXFLAGS -= -O2
#QMAKE_CXXFLAGS -= -O3
INCLUDEPATH += /home/zerlok/nsu_prog/graphics/logger
INCLUDEPATH += /home/zerlok/nsu_prog/oop/task11


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
    main.cpp

# Custom shaders.
SOURCES += \
    shaders/metamorphose_shader.cpp \
    shaders/screwshader.cpp

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

SOURCES += ../logger/logger.cpp

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
    engine.hpp

# Custom shaders.
HEADERS += \
    shaders/metamorphose_shader.h \
    shaders/screwshader.hpp

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

HEADERS += ../logger/logger.hpp
