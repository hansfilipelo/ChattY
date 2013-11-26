/*
FILNAMN: 		netClient.cc
PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
SKAPAD DATUM:	2013-11-19
BESKRIVNING:	
*/

#include "netClient.h"
#include <QTest>

using namespace std;

NetClient::NetClient(string username, QObject *parent) : QObject(parent){
    
    name=QString::fromStdString(username);
}
void NetClient::test2(){

    tcpSocket->write("Hej2 \n\r");
}

void NetClient::test(){
    tcpSocket = new QTcpSocket(this);
    //Connect all signals and slots
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    
    qDebug() << "connecting...";
    
    tcpSocket->connectToHost(QHostAddress("127.0.0.1"),quint16(1234));
    
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
    this->test2();
}


