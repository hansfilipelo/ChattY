#
# FILNAMN: 		server.pro
# PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
# SKAPAD DATUM:		2013-11-17
# BESKRIVNING:		Project file for Qmake. Creates makefile compatible with make and c++ compilers

# Use GNU compilers - not clang
QMAKE_CXX	= /usr/bin/g++
QMAKE_CC	= /usr/bin/gcc

# C++11 standard
QMAKE_CXXFLAGS  += -std=c++11

# Qt components required. Server does not use GUI. 
QT		+= core
QT		+= network
QT		-= gui

TARGET		= server

CONFIG		+= console
CONFIG		-= app_bundle

TEMPLATE	= app

# Files to include while building
SOURCES		+= getTime.cc master/master.cc room/room.cc user/User.cc message/message.cc

HEADERS		+= master/master.h room/room.h message/message.h

