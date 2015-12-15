TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	datapackage.cpp \
    sender.cpp \
    receiver.cpp \
	media.cpp

HEADERS += \
	datapackage.h \
    sender.h \
    receiver.h \
	media.h \
	xprotocol.h

OTHER_FILES += gtest.cpp
