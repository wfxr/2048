#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T11:28:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
    ../core/board.cpp \
    ../core/game.cpp \
    ../core/subject.cpp \
    qtile.cpp \
    gui2048.cpp

HEADERS  += \
    ../core/board.h \
    ../core/direction.h \
    ../core/game.h \
    ../core/observer.h \
    ../core/subject.h \
    qtile.h \
    gui2048.h

DISTFILES += \
    build-gui-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/gui.ilk \
    build-gui-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/gui.pdb \
    build-gui-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/gui.exe
