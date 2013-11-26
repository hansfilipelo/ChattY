/*
FILNAMN: 		main.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include <QtCore/QCoreApplication>
#include "master/master.h"
#include "serverclass/server.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);
    
    Master* master = new Master();
    Server server(master);
    server.start();
    
    return app.exec();
}
