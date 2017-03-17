#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T17:14:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFFmepg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32
{
}

macx
{

INCLUDEPATH += /Users/yuqiaomiao/QtFFmepg/QtFFmepg/libFFmpeg/include

LIBS += -L/Users/yuqiaomiao/QtFFmepg/QtFFmepg/libFFmpeg/lib

LIBS += -lavcodec   \
        -lavdevice  \
        -lavfilter  \
        -lavformat  \
        -lavutil    \
        -lswscale
}


SOURCES += main.cpp\
        mainwindow.cpp \
    h264decoder.cpp \
    cameraclient.cpp

HEADERS  += mainwindow.h \
    h264decoder.h \
    cameraclient.h \
    cctcpdatadefine.h

FORMS    += mainwindow.ui
