/*
FILNAMN: 		server.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "server.h"


using namespace std;

Server::Server(Master* masterptr, QObject *parent) : QTcpServer(parent)
{
    masterPointer=masterptr;
}


void Server::start()
{
    if(!this->listen(QHostAddress::Any,40001))
    {
        qDebug() <<"could not start server";
    }
}


void Server::incomingConnection(qintptr handle)
{
    Thread *currentThread = new Thread(handle, masterPointer, this);
    
    connect(currentThread,SIGNAL(finished()),currentThread,SLOT(deleteLater()));
    currentThread->start();
}
