#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:25:45
#
#-------------------------------------------------

QMAKE_CXX	= g++
QMAKE_CC	= gcc

QT		+= core gui network widgets
ICON		= icon/ChattY.icns
RC_FILE		= ChattY.rc

TARGET		= ChattY
TEMPLATE	= app

CONFIG		+= c++11
CONFIG		+= release

# ---- Files ----

SOURCES += main.cpp chatwindow.cpp logindialog.cpp ../client/NetClient.cc \
    gui.cpp \

HEADERS  += chatwindow.h logindialog.h ../client/NetClient.h \
    gui.h \

FORMS    += chatwindow.ui logindialog.ui

RESOURCES += \
    myResources.qrc
