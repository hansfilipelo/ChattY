/*
FILNAMN: 		server.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "server.h"

using namespace std;

Server::Server(QObject *parent) : QTcpServer(parent)
{
}


void Server::startServer()
{
    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug() <<"could not start server";
    }
    else
    {
        qDebug() <<"Listening...";
    }
}


void Server::incomingConnection(qintptr handle)
{
    qDebug() << handle <<"Connecting...";
    Thread *currentThread = new Thread(handle,this);
    connect(currentThread,SIGNAL(finished()),currentThread,SLOT(deleteLater()));
    currentThread->start();
}

