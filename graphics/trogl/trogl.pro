TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++11 -lglut -lGL -lGEW -lGLU
LIBS += -lglut -lGL -lGLEW -lGLU


QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG -= -O1 -O2 -O3


INCLUDEPATH += /home/zerlok/nsu_prog/include
LIBS += -L/home/zerlok/nsu_prog/libs -llogger


SOURCES += \
    component.cpp \
	object.cpp \
	camera.cpp \
	shader.cpp \
	texture.cpp \
	material.cpp \
	mesh.cpp \
	light.cpp \
	scene.cpp \
	gui.cpp \
	engine.cpp \
	main.cpp
SOURCES += \
	shaders/metamorphose_shader.cpp \
	shaders/screwshader.cpp \
	materials/diffusematerial.cpp \
    meshes/cube.cpp \
    meshes/strangecube.cpp \
	meshes/megacube.cpp \
	meshes/cylinder.cpp \
    lamps/lamp.cpp \
    gui/guifps.cpp \
    gui/guilabel.cpp \
    gui/guiplane.cpp \
	common/color.cpp \
	common/utils.cpp \

HEADERS += \
	opengls.hpp \
	component.hpp \
	object.hpp \
	camera.hpp \
	shader.hpp \
	texture.hpp \
	material.hpp \
	mesh.hpp \
	light.hpp \
	scene.hpp \
	gui.hpp \
	engine.hpp
HEADERS += \
	shaders/metamorphose_shader.h \
	shaders/screwshader.hpp \
	materials/diffusematerial.hpp \
	meshes/strangecube.hpp \
	meshes/cube.hpp \
	meshes/megacube.hpp \
	meshes/cylinder.hpp \
	lamps/lamp.hpp \
	gui/guilabel.hpp \
	gui/guifps.hpp \
	gui/guiplane.hpp \
    common/color.hpp \
	common/utils.h
