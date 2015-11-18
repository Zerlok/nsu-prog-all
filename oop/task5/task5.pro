TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
	node.cpp

HEADERS += \
    node.h

OTHER_FILES += gtest.cpp \
	../build/task5/test01-input.txt \
	../build/task5/test02-input.txt \
	../build/task5/test01-output.txt \
	../build/task5/test02-output.txt \
	../build/task5/test03-input.txt \
	../build/task5/test03-output.txt
