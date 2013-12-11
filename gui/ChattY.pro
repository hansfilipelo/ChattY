#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:25:45
#
#-------------------------------------------------

QMAKE_CXX	= g++
QMAKE_CC	= gcc

QT		+= core gui
QT              +=network gui testlib
ICON		= icon/ChattY.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET		= ChattY
TEMPLATE	= app

CONFIG		+= c++11

# ---- Files ----

SOURCES += main.cpp chatwindow.cpp logindialog.cpp ../client/NetClient.cc \
    gui.cpp

HEADERS  += chatwindow.h logindialog.h ../client/NetClient.h \
    gui.h

FORMS    += chatwindow.ui logindialog.ui

RESOURCES += \
    myResources.qrc
