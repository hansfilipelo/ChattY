/*
FILNAMN: 		server.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "thread.h"

using namespace std;

Thread::Thread(qintptr ID,QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void Thread::run()
{
    //thread starts here
    qDebug() << socketDescriptor << "starting thread";
    chattySocket = new QTcpSocket();
    if(!chattySocket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(chattySocket->error());
        return;
    }
    
    connect(chattySocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(chattySocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    qDebug() << socketDescriptor << "client connected";
    
    //creates a messageloop
    exec();
    
}

void Thread::readyRead()
{
    QByteArray Data =chattySocket->readAll();
    
    qDebug() << socketDescriptor << "Data in: "<< Data;

    chattySocket->write(Data);
}


void Thread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    
    chattySocket->deleteLater();
    //exits the thread
    exit(0);
}