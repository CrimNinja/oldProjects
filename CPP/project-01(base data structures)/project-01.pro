TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    splitter.cpp \
    fileread.cpp \
    usercommands.cpp

HEADERS += \
    splitter.h \
    fileread.h \
    usercommands.h \
