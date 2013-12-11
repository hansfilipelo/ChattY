/*
 FILNAMN: 		server.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-18
 BESKRIVNING:
 */

#include "thread.h"

using namespace std;


// ---------------------------------------
// Helper functions

void Thread::handleMessage(QString inData){
    int i;
    
    QString from;
    i = inData.indexOf(compare);
    from = inData.left(i);
    string stdFrom = from.toStdString();
    inData = inData.mid(i+1);
    
    QString to;
    i = inData.indexOf(compare);
    to = inData.left(i);
    string stdTo = to.toStdString();
    inData = inData.mid(i+1);
    
    QString contents;
    i = inData.indexOf(compare);
    contents = inData.left(i);
    string stdContents = contents.toStdString();
    inData = inData.mid(i+1);
    
    cout << "readyRead" << endl;
    cout << stdFrom << endl;
    cout << stdTo << endl;
    cout << stdContents << endl;
    
    
    Message message(stdContents, stdFrom, stdTo);
    userPointer->sendMessage(message);
}

// ----------------------

void Thread::handleInitiate(string stdInData) {
    try
    {
        userPointer = masterPointer->createUser(stdInData);
        userPointer->setThread(this);
    }
    catch (...)
    {
        reinitiate();
    }
}

// ----------------------

void Thread::handleStructure() {
    vector<string> structure = userPointer->getStruct();
    
    QByteArray sendData;
    sendData += "/structure";
    sendData += compare;
    
    for (unsigned int i = 0; i < structure.size() ; i++) {
        sendData += QString::fromStdString(structure.at(i));
        sendData += compare;
    }
    
    TcpSocket->write(sendData);
    
}


// ---------------------------------------

Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
    compare += 0x1F;
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
    
    int i = Data.indexOf(compare);
    
    QString commandName = Data.left(i);
    QString inData = Data.mid(i+1);
    QString temp = inData;
    string stdInData = temp.toStdString();
    
    // Check which command that's supposed to run
    if (commandName == "/initiate") {
        handleInitiate(stdInData);
    }
    
    else if (commandName == "/message") {
        handleMessage(inData);
    }
    
    else if ( commandName == "/structure" ) {
        handleStructure();
    }
    
    else {
        TcpSocket->write("Ej giltigt kommando");
        cout << socketDescriptor << "Data in: "<< stdInData<<endl;
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
void Thread::sendMessage(Message messageObject){
    QByteArray array = "/message";
    array += 0x1F; //unit separator
    array += QString::fromStdString(messageObject.getFrom());
    array += 0x1F;
    array += QString::fromStdString(messageObject.getTo());
    array += 0x1F;
    array += QString::fromStdString(messageObject.getMessage());
    array += 0x1F;
    array += QString::fromStdString(messageObject.getServerTime());
    array += 0x1F;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}


void Thread::sendHistory(){
    QByteArray array = "/history";
    array += 0x1F; //unit separator

    for (unsigned int i=0; i<userPointer->getParentRoom()->log.size(); ++i)
    {
        Message tempMessage = userPointer->getParentRoom()->log.at(i);
        
        array += QString::fromStdString(tempMessage.getFrom());
        array += 0x1F; //unit separator
        array += QString::fromStdString(tempMessage.getTo());
        array += 0x1F; //unit separator
        array += QString::fromStdString(tempMessage.getMessage());
        array += 0x1F; //unit separator
        array += QString::fromStdString(tempMessage.getServerTime());
        array += 0x1F; //unit separator
    }
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}


void Thread::reinitiate(){
    QByteArray array = "/reinitiate";
    array += 0x1F; //unit separator
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

