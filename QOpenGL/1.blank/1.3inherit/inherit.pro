#-------------------------------------------------
#
# Project created by QtCreator 2022-07-04T16:03:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLWidget
TEMPLATE = app

win32{
    LIBS+=-lopengl32
}

SOURCES += main.cpp\
        glwidget.cpp

HEADERS  += glwidget.h
