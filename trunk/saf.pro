# -------------------------------------------------
# Project created by QtCreator 2010-11-05T10:11:30
# -------------------------------------------------
QT += core \
    gui
TARGET = saf
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    shark.cpp \
    fish.cpp \
    sea.cpp \
    rand.cpp \
    animal.cpp \
    optionwindow.cpp \
    simulation.cpp \
    qmylabel.cpp \
    statistic.cpp
HEADERS += mainwindow.h \
    animal.h \
    shark.h \
    fish.h \
    sea.h \
    rand.h \
    optionwindow.h \
    simulation.h \
    animals.h \
    qmylabel.h \
    statistic.h
FORMS += mainwindow.ui \
    options.ui
RESOURCES += ressources.qrc
LIBS += -L"./qwt/"
LIBS += -lqwt
