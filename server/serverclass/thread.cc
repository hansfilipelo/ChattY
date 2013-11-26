/*
FILNAMN: 		server.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-18
BESKRIVNING:	
*/

#include "thread.h"

using namespace std;

Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
}

void Thread::run()
{
    //thread starts here
    qDebug() << socketDescriptor << "starting thread";
    TcpSocket = new QTcpSocket();
    
    
    if(!TcpSocket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(TcpSocket->error());
        return;
    }
    
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    qDebug() << socketDescriptor << "client connected";
    
    //creates a messageloop
    exec();
    
}

void Thread::readyRead()
{
    QByteArray Data = TcpSocket->readAll();
    
    string inData = Data.data();
    
    string commandName;
    while (inData.front!="*")
    {
        commandName.append[inData.front()];
        inData.erase(inData.begin());
    }
    switch (commandName)
    {
        case "/initiate": userPointer = masterPointer->createUser(inData);
            break;
            /*
        case "/message": userPointer->createMessage(inData);
            break;
        case "/room": userPointer->createRoom(inData);
            break;*/
        default: TcpSocket->write("Ej giltigt kommando");
            break;
    }
   // qDebug() << socketDescriptor << "Data in: "<< inData;
}




void Thread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    
    TcpSocket->deleteLater();
    //exits the thread
    exit(0);
}