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
    tcpSocket = new QTcpSocket(this);
    
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    
    qDebug() << "connecting...";
    tcpSocket->connectToHost(QHostAddress(address),quint16(1234));
    
    if(!tcpSocket->waitForConnected(1000)){
        qDebug() << "Error: " << tcpSocket->errorString();
    }
}


//------Slots---------

void NetClient::connected(){
    qDebug() << "Connected!";
    QByteArray array = "/initiate*";
    array += name;
    
    tcpSocket->write(array);
    
    }

void NetClient::disconnected(){
    qDebug() << "disconnected";
    
}

void NetClient::bytesWritten(qint64 bytes){
    qDebug() << "we wrote: " << bytes;
    
}

void NetClient::readyRead(){
    qDebug() << "reading...";
    qDebug() << tcpSocket->readAll();
}

void NetClient::sendMessage(string message){
    qDebug() <<"message sent";
}


