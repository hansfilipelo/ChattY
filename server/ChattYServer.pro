#
# FILNAMN: 		server.pro
# PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
# SKAPAD DATUM:		2013-11-17
# BESKRIVNING:		Project file for Qmake. Creates makefile compatible with make and c++ compilers

# Use GNU compilers - not clang
QMAKE_CXX	= g++
QMAKE_CC	= gcc

# Qt components required. Server does not use GUI. 
QT		+= core
QT		+= network
QT		-= gui

TARGET		= ChattYServer

# Use C++11 standard
CONFIG		+= console c++11
CONFIG		-= app_bundle

TEMPLATE	= app

# Files to include while building
SOURCES		+= main.cc getTime.cc master/master.cc room/room.cc user/User.cc message/message.cc serverclass/server.cc serverclass/thread.cc

HEADERS		+= master/master.h room/room.h message/message.h serverclass/thread.h serverclass/server.h

