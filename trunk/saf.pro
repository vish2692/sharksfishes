#-------------------------------------------------
#
# Project created by QtCreator 2010-11-05T10:11:30
#
#-------------------------------------------------

QT       += core gui

TARGET = saf
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shark.cpp \
    fish.cpp \
    sea.cpp \
    rand.cpp \
    animal.cpp \
    optionwindow.cpp

HEADERS  += mainwindow.h \
    animal.h \
    shark.h \
    fish.h \
    sea.h \
    rand.h \
    optionwindow.h

FORMS    += mainwindow.ui \
    options.ui

RESOURCES += \
    ressources.qrc
