TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += class.h factory.h \
    point.h \
    rectangle.h \
    circle.h \
	shape.h \
	list.h \
	../task1/recordarray.h \
    extrastring.h
SOURCES += class.c factory.c main.c \
    point.c \
    rectangle.c \
	circle.c \
	list.c \
	../task1/recordarray.c \
    extrastring.c
