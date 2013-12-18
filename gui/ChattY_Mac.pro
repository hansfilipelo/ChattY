#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:25:45
#
#-------------------------------------------------

QMAKE_CXX	= g++
QMAKE_CC	= gcc

QMAKE_POST_LINK	+= ./postCompile.sh

QT		+= core gui network widgets multimedia
ICON		= icon/ChattY.icns
RC_FILE		= ChattY.rc

win32:DEFINES	+= __WINDOWS_BUILD__
macx:DEFINES	+= __MACOSX_BUILD__

TARGET		= ChattY
TEMPLATE	= app

CONFIG		+= c++11
CONFIG		+= release

# ---- Files ----

SOURCES += main.cpp chatwindow.cpp logindialog.cpp NetClient.cc \
    gui.cpp \

HEADERS  += chatwindow.h logindialog.h NetClient.h \
    gui.h \

FORMS    += chatwindow.ui logindialog.ui

RESOURCES += \
    myResources.qrc
