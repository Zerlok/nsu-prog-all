TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	datapackage.cpp \
    sender.cpp \
    receiver.cpp \
	media.cpp \
    xprotocol.cpp

HEADERS += \
	datapackage.h \
    sender.h \
    receiver.h \
	media.h \
	xprotocol.h \
    factory.h

OTHER_FILES += gtest.cpp \
    ../build/task7/normal-media-test.txt
