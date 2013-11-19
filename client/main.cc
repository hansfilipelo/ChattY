/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-19
BESKRIVNING:	
*/

#include "netClient.h"
#include <QCoreApplication>

int main(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);
    
    NetClient mTest;
    mTest.test();
    return a.exec();
}