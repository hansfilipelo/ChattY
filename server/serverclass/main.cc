/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include <QtCore/QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    
    QCoreApplication app(argc,argv);
    
    Server mserver;
    mserver.startServer();
    
    return app.exec();
}