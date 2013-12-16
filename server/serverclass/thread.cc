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

void Thread::handleHistory() {
    int i;
    
    QString nrOfDays;
    i = inData.indexOf(compare);
    nrOfDays = inData.left(i);
    
    bool ok;
    int daysBack = nrOfDays.toInt(&ok);
    
    if ( not(ok) ) {
        Message message("Did not receive int for which day to get history for",userPointer->getParentRoom()->getName( userPointer->getName());
        userPointer->sendMessage(message);
    }
    else {
        vector<Message> oldLog = userPointer->getParentRoom()->readOldFromFile(daysBack);
        
        QByteArray array = "/oldHistory";
        array += 0x1F; //unit separator
        
        logSize = oldLog.size();
        
        for (unsigned int i = 0; i < logSize; i++){
            
            Message tempMessage = oldLog.at(i);
            
            array += QString::fromStdString(tempMessage.getFrom());
            array += compare; //unit separator
            array += QString::fromStdString(tempMessage.getTo());
            array += compare; //unit separator
            array += QString::fromStdString(tempMessage.getMessage());
            array += compare; //unit separator
            array += QString::fromStdString(tempMessage.getServerTime());
            if ( i+1 == logSize ){
                array += breaker;
                break;
            }
            array += compare; //unit separator
        }
        TcpSocket->write(array);
        TcpSocket->waitForBytesWritten(1000);

    }
}

// ---------------

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
    
    Message message(stdContents, stdFrom, stdTo);
    userPointer->sendMessage(message);
}

// ----------------------

void Thread::handleInitiate(string stdInData) {
    try
    {
        // Creates user
        userPointer = masterPointer->createUser(stdInData);
        userPointer->setThread(this);
        
        // Sends "OK username is accepted" to client
        QByteArray array = "/userAccepted";
        array += compare;
        array+= breaker;
        
        TcpSocket->write(array);
        TcpSocket->waitForBytesWritten(1000);
        
        // Sends structure to "the other side"
        handleStructure();
        userPointer->sendHistory();
        
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
    unsigned int i;
    
    for (i = 0; i < (structure.size()-1)  ; i++) {
        sendData += QString::fromStdString(structure.at(i));
        sendData += compare;
    }
    sendData += QString::fromStdString(structure.at(i));
    sendData += breaker;
    
    TcpSocket->write(sendData);
    
}


// ---------------------------------------

Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
    compare += 0x1F;
    breaker += 0x1E;
    userPointer = nullptr;
}

// ---------------------------------------

void Thread::run()
{
    //thread starts here
    TcpSocket = new QTcpSocket();
    
    
    if(!TcpSocket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(TcpSocket->error());
        return;
    }
    
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    
    //creates a messageloop
    exec();
    
}

// ---------------------------------------


// ---------------------------

void Thread::readyRead()
{
    
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
        if (commandName == "/initiate") {
            handleInitiate(stdInData);
        }
        
        else if (commandName == "/message") {
            handleMessage(inData);
        }
        
        else if ( commandName == "/structure" ) {
            handleStructure();
        }
        
        else if ( commandName == "/oldHistory" ) {
            handleHistory(inData);
        }
        
        else {
            cout << "Ej giltigt kommando" << commandName.toStdString() << endl;
            TcpSocket->write("Ej giltigt kommando");
            cout << socketDescriptor << "Data in: "<< stdInData<<endl;
        }

        inData = rest;
        n = inData.indexOf(breaker);
        
    }while (n != -1 );
}

// ---------------------------------------

void Thread::disconnected()
{
    try {
        if (userPointer != nullptr) {
            masterPointer->removeUser(userPointer->getName());
        }
    } catch (...) {
        
    }
    
    masterPointer->updateStructForAll();
    
    TcpSocket->deleteLater();
    //exits the thread
    exit(0);
}

// -----------------------------------------

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
    array += 0x1E;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}

// -----------------------------------------

void Thread::sendHistory(){
    QByteArray array = "/history";
    array += 0x1F; //unit separator
    unsigned int logSize = userPointer->getParentRoom()->log.size();
    
    for (unsigned int i = 0; i < logSize; i++){
        
        Message tempMessage = userPointer->getParentRoom()->log.at(i);
        
        array += QString::fromStdString(tempMessage.getFrom());
        array += compare; //unit separator
        array += QString::fromStdString(tempMessage.getTo());
        array += compare; //unit separator
        array += QString::fromStdString(tempMessage.getMessage());
        array += compare; //unit separator
        array += QString::fromStdString(tempMessage.getServerTime());
        if ( i+1 == logSize ){
            array += breaker;
            break;
        }
        array += compare; //unit separator
    }
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    
}

// -----------------------------------------

void Thread::reinitiate(){
    QByteArray array = "/reinitiate";
    array += 0x1F;
    array += 0x1E; //unit separator
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
    disconnected();
}

// -----------------------------------------


void Thread::requestStruct() {
    QByteArray array = "/requestStruct";
    array += 0x1F;
    array += 0x1E;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}
