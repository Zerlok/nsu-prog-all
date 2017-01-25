#TEMPLATE = app
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

#SOURCES += \
#    logger.cpp \
#    main.cpp \
#    myclass.cpp

#HEADERS += \
#    logger.hpp \
#    myclass.h

TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    logger.cpp

HEADERS += \
    logger.hpp
