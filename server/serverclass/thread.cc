/*
 FILNAMN: 		server.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-18
 BESKRIVNING:
 */

#include "thread.h"
#include "../message/message.h"
#include "../room/room.h"

using namespace std;

Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
}

// ---------------------------------------

void Thread::run()
{
    //thread starts here
    cout << socketDescriptor << " starting thread"<<endl;
    TcpSocket = new QTcpSocket();
    
    
    if(!TcpSocket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(TcpSocket->error());
        return;
    }
    
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    cout << socketDescriptor << " client connected"<<endl;
    
    //creates a messageloop
    exec();
    
}

// ---------------------------------------

void Thread::readyRead()
{
    QByteArray Data = TcpSocket->readAll();
    
    // Separate the command from the operand
    QByteArray compare;
    compare += 0x1F;
    
    int i = Data.indexOf(compare);
    
    QString commandName = Data.left(i);
    QString temp = Data.mid(i);
    
    string inData = temp.toStdString();
    
    // Check which command that's supposed to run
    if (commandName == "/initiate") {
        try
        {
            userPointer = masterPointer->createUser(inData);
            userPointer->setThread(this);
        }
        catch (...)
        {
            reinitiate();
        }
    }
    
    else if (commandName == "/message") {
        Message message(inData, userPointer->getName(), userPointer->getParentRoom()->getName());
        userPointer->sendMessage(message);
    }
    else {
        TcpSocket->write("Ej giltigt kommando");
        cout << socketDescriptor << "Data in: "<< inData<<endl;
    }
}

// ---------------------------------------

void Thread::disconnected()
{
    cout << socketDescriptor << "Disconnected"<<endl;
    try {
        masterPointer->removeUser(userPointer->getName());
    } catch (...) {
        
    }
    
    TcpSocket->deleteLater();
    //exits the thread
    exit(0);
}

//svarar klienten
void Thread::sendMessage(string inMessage){
    QByteArray array = "/message";
    array += 0x1F; //unit separator
    
    QString Data;
    Data += QString::fromStdString(inMessage);
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}

void Thread::reinitiate(){
    QByteArray array = "/reinitiate";
    array += 0x1F; //unit separator
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}


