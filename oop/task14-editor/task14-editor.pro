TASKNAME = Editor

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11 -lpthread -lgtest

LIBS += -lpthread -lgtest
INCLUDEPATH += /usr/include/gtest


SOURCES += main.cpp \
    editor.cpp \
    commandparser.cpp \
	history.cpp \
    editorerrors.cpp \
    stringutils.cpp

HEADERS += \
	bigvector.h \
	serdeser.h \
    command.h \
    copycommand.h \
    insertcommand.h \
    searchreplacecommand.h \
    undocommand.h \
    redocommand.h \
    editor.h \
    commandparser.h \
    factory.h \
    helpcommand.h \
    setcommand.h \
    history.h \
    editorerrors.h \
    stringutils.h

OTHER_FILES += gtest.cpp
