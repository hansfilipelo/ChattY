/*
FILNAMN: 		netClient.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-19
BESKRIVNING:	
*/

#include "netClient.h"
#include <QTest>

using namespace std;

NetClient::NetClient(string username, string inAddress, QObject *parent) : QObject(parent){
    
    name=QString::fromStdString(username);
    address=QString::fromStdString(inAddress);
}


void NetClient::start(){
    TcpSocket = new QTcpSocket(this);
    
    connect(TcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    
    qDebug() << "connecting...";
    TcpSocket->connectToHost(QHostAddress("127.0.0.1"),quint16(1234));
    
    if(!TcpSocket->waitForConnected(1000)){
        qDebug() << "Error: " << TcpSocket->errorString();
    }
}


//------Slots---------

void NetClient::connected(){
    qDebug() << "Connected!";
    QByteArray array = "/initiate*";
    array += name;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(3000);
    }

void NetClient::disconnected(){
    qDebug() << "disconnected";
    
}

void NetClient::bytesWritten(qint64 bytes){
    qDebug() << "we wrote: " << bytes;
    
}

void NetClient::readyRead(){
    qDebug() << "reading...";
    qDebug() << TcpSocket->readAll();
}

void NetClient::sendMessage(string message){
    QByteArray array = "/message*";
    array += message;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(3000);
}


