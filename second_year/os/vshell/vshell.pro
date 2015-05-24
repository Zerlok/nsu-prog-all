TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += main.h\
        debug.h\
        array.h\
        cmd.h\
        parser.h\
        proc.h\
        vshell.h\
    launcher.h \
    streams.h

SOURCES += main.c\
        array.c\
        cmd.c\
        parser.c\
        proc.c\
        vshell.c \
    launcher.c \
    streams.c
