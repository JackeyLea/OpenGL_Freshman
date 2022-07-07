#-------------------------------------------------
#
# Project created by QtCreator 2022-07-07T11:54:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = translate
TEMPLATE = app

win32{
    LIBS+=-lopengl32
}

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
