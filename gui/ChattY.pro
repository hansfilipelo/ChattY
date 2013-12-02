#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:25:45
#
#-------------------------------------------------

QT	+= core gui
ICON	= icon/ChattY.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChattY
TEMPLATE = app


SOURCES += main.cpp\
        chatwindow.cpp \
    logindialog.cpp

HEADERS  += chatwindow.h \
    logindialog.h

FORMS    += chatwindow.ui \
    logindialog.ui
