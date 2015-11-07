TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	graph.cpp

HEADERS += graph.h \
    treebuilder.h

OTHER_FILES += gtest.cpp \
    ../build/task4/test01-input.txt \
    ../build/task4/test01-output.txt \
    ../build/task4/test02-input.txt \
    ../build/task4/test02-output.txt \
    ../build/task4/test03-input.txt \
    ../build/task4/test03-output.txt \
    ../build/task4/test04-input.txt \
    ../build/task4/test04-output.txt
