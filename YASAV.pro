#-------------------------------------------------
#
# Project created by QtCreator 2019-04-07T18:24:42
#
# Yet Another Sorting Algorhytm Visualiser
# By Dmitriy Gershenkop a.k.a. BortEngineerDude
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YASAV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        yasav.cpp \
    array/arraymodel.cpp \
    array/arrayviewer.cpp \
    sort/bubble.cpp \
    sort/sorter.cpp \
    sort/selection.cpp \

HEADERS  += yasav.h \
    array/arraymodel.h \
    array/arrayviewer.h \
    sort/bubble.h \
    sort/sorter.h \
    sort/selection.h \

FORMS    += yasav.ui
