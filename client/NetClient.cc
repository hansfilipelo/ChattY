/*
 FILNAMN: 		NetClient.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include "NetClient.h"
#include "../Gui/Gui.h"
#include <QTest>

using namespace std;

NetClient::NetClient(string username, string inAddress, Gui* myGui, QObject *parent) : QObject(parent){
    
    name=QString::fromStdString(username);
    address=QString::fromStdString(inAddress);
}


void NetClient::start(){
    TcpSocket = new QTcpSocket(this);
    
    connect(TcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    
    
    qDebug() << "connecting...";
    
    TcpSocket->connectToHost(QHostAddress(address),quint16(1234));
    
    if(!TcpSocket->waitForConnected(1000)){
        qDebug() << "Error: " << TcpSocket->errorString();
    }
}


//------Slots---------

void NetClient::connected(){
    qDebug() << "Connected!";
    QByteArray array = "/initiate";
    array += 0x1F; //unit separator
    array += name;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::disconnected(){
    qDebug() << "disconnected";
    
}

void NetClient::readyRead(){
    //Recieve commando
    QByteArray Data = TcpSocket->readAll();
    
    // Separate the command from the operand
    QByteArray compare;
    compare += 0x1F;
    
    int i = Data.indexOf(compare);
    
    QString commandName = Data.left(i);
    QString inData = Data.mid(i);
    
    // Check which command that's supposed to run
    if (commandName == "/reinitiate") {
        guiPointer->userNameTaken();
    }
    
    else (commandName == "/message") {
        
        // Get from
        i = inData.indexOf(compare);
        QString from = inData.left(i);
        inData = inData.mid(i);
        
        // Get to
        i = inData.indexOf(compare);
        QString to = inData.left(i);
        inData = inData.mid(i);
        
        // Get message
        i = inData.indexOf(compare);
        QString contents = inData.left(i);
        inData = inData.mid(i);
        
        // Get time
        QString dateTime = inData;
        
        guiPointer->receiveMssage(from, to, contents, dateTime);
    }
}

void NetClient::sendMessage(QString from, QString to, QString message){
    QByteArray array = "/message";
    array += 0x1F; //unit separator
    array += from;
    array += 0x1F;
    array += to;
    array += 0x1F;
    array += message;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::setName(Qstring inName) {
    name=inName;
}


