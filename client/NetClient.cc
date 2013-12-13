/*
 FILNAMN: 		NetClient.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include "NetClient.h"
#include "../gui/gui.h"
#include <QTest>

using namespace std;

NetClient::NetClient(QString username, QString inAddress, Gui* myGui, QObject *parent) : QObject(parent){
    
    guiPointer = myGui;
    name=username;
    address=inAddress;
    compare += 0x1F;
    breaker +=0x1E;
}


void NetClient::start(){
    TcpSocket = new QTcpSocket(this);
    
    connect(TcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    
    
    qDebug() << "connecting...";
    
    QHostInfo info = QHostInfo::fromName(address);
    
    TcpSocket->connectToHost(info.addresses().at(0),quint16(40001));
    
    if(!TcpSocket->waitForConnected(1000)){
        guiPointer->noConnection();
        qDebug() << "Error: " << TcpSocket->errorString();
    }
}


//------Slots---------

void NetClient::connected(){
    QByteArray array = "/initiate";
    array += 0x1F; //unit separator
    array += name;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::disconnected(){
    qDebug() << "disconnected";
    
}

void NetClient::readyRead(){
    
    QByteArray Data = TcpSocket->readAll();
    
    int i;
    
    QString commandName;
    QString inData = Data;
    
    int n = inData.indexOf(breaker);
    QString rest;
    
    
    do {
        rest = inData.mid(n+1);
        inData = inData.left(n);
        i = inData.indexOf(compare);
        
        commandName = inData.left(i);
        
        inData = inData.mid(i+1);
        
        QString temp = inData;
        string stdInData = temp.toStdString();
        
        // Check which command that's supposed to run
        if (commandName == "/reinitiate") {
            guiPointer->userNameTaken();
            break;
        }
        
        else if ( commandName == "/userAccepted") {
            guiPointer->connected();
        }
        
        else if (commandName == "/history") {
            handleHistory(inData);
        }
        
        
        else if (commandName == "/message") {
            handleMessage(inData);
        }
        
        else if ( commandName == "/requestStruct") {
            handleRequestStruct();
        }
        
        else if ( commandName == "/structure" ) {
            handleStructure(inData);
        }
        else {
            throw logic_error("Unknown command");
        }
        
        inData = rest;
        n = inData.indexOf(breaker);
        
    }while (n != -1 );
}

void NetClient::sendMessage(QString from, QString to, QString message){
    QByteArray array = "/message";
    qDebug() << "sendMessage";
    array += 0x1F; //unit separator
    array += from;
    array += 0x1F;
    array += to;
    array += 0x1F;
    array += message;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::setName(QString inName) {
    name=inName;
}

void NetClient::getStruct(){
    QByteArray array = "/structure";
    array += 0x1E;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

//--------------------------------------------
//Helpfunctions

void NetClient::handleRequestStruct(){
    QByteArray array = "/structure";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::handleMessage(QString inData){
    
    int i;
    // Get from
    i = inData.indexOf(compare);
    QString from = inData.left(i);
    inData = inData.mid(i+1);
    
    // Get to
    i = inData.indexOf(compare);
    QString to = inData.left(i);
    inData = inData.mid(i+1);
    
    // Get message
    i = inData.indexOf(compare);
    QString contents = inData.left(i);
    inData = inData.mid(i+1);
    
    // Get time
    QString dateTime = inData;
    
    guiPointer->receiveMessage(from, to, contents, dateTime);
    
}

void NetClient::handleHistory(QString inData){
    QVector<QString> history;
    int i = inData.indexOf(compare);
    while(i != -1 ){
        
        // Get from
        i = inData.indexOf(compare);
        QString from = inData.left(i);
        inData = inData.mid(i+1);
        history.push_back(from);
        
        // Get to
        i = inData.indexOf(compare);
        QString to = inData.left(i);
        inData = inData.mid(i+1);
        history.push_back(to);
        
        // Get message
        i = inData.indexOf(compare);
        QString contents = inData.left(i);
        inData = inData.mid(i+1);
        history.push_back(contents);
        
        
        //Get time
        i = inData.indexOf(compare);
        QString time = inData.left(i);
        inData = inData.mid(i+1);
        history.push_back(time);
    }
    guiPointer->receiveHistory(history);
}


void NetClient::handleStructure(QString inData){
    QVector<QString> output;
    int i = inData.indexOf(compare);
    while(i  != -1){
        QString data = inData.left(i);
        inData = inData.mid(i+1);
        output.push_back(data);
        qDebug() << data;
        
        i = inData.indexOf(compare);
    }
    
    output.push_back(inData);
    
    guiPointer->updateStruct(output);
    
}
