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
/*Function that handles both, /history and /oldHistory.
 *Firstly it checks if the int conversion could be properly handled. 
 *readOldFromFile(daysback) will read all messages, daysBack number of days ago
 *these will be saved in oldLog and serialized. The try catch is necessary to keep
 *the server from crashing in the event that the user does not exist since getName 
 * throws.
 */
void Thread::handleHistory(QString inData) {
    
    bool ok;
    int daysBack = inData.toInt(&ok);
    
    if ( not(ok) ) {
        Message message("Did not receive int for which day to get history for",userPointer->getParentRoom()->getName(), userPointer->getName());
        userPointer->receiveMessage(message);
    }
    else {
        vector<Message> oldLog = userPointer->getParentRoom()->readOldFromFile(daysBack);
        
        QByteArray array = "/oldHistory";
        array += 0x1F; //unit separator
        
        int logSize = oldLog.size();
        
        if (logSize == 0){
            array += breaker;
        }else{
            for (int i = 0; i < logSize; i++){
                
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
            }}
        TcpSocket->write(array);
        
        if(!TcpSocket->waitForBytesWritten(5000)){
            try{
                cout << "Couldn't write to client: " << "oldHistory" << "from: " << userPointer->getName() <<  endl;
            }catch(...){
            }
        }
        
    }
}

// ---------------
/*Deserialization of message sent from NetClient and pass it along to the user's
 *sendMessage function serverside.
 */

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

/*Deserialization of name and, when name is not take a userAccepted command is sent
 *back to the client to notify that everything went okay.
 */

void Thread::handleInitiate(string stdInData) {
    try{
        // Creates user
        userPointer = masterPointer->createUser(stdInData);
        userPointer->setThread(this);
        
        // Sends "OK username is accepted" to client
        QByteArray array = "/userAccepted";
        array += compare;
        array+= breaker;
        
        TcpSocket->write(array);
        
        if(!TcpSocket->waitForBytesWritten(5000)){
            try{
                cout << "Couldn't write to client: " << "userAccepted" << "from: " << userPointer->getName() <<  endl;
            }catch(...){
            }
        }
        //updates what day it is
        userPointer->getParentRoom()->setFilePath();
        
        // Sends structure to "the other side"
        this->sendHistory();
        handleStructure();
        
    }
    catch (...)
    {
        reinitiate();
    }
}

// ----------------------

//Serialization of structure (of rooms and users) before it is sent to the client.

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
    TcpSocket->waitForBytesWritten(5000);
    
}


// ---------------------------------------

/*Constructor for our thread, specifying the data and call separators, compare 
 *and breaker.
 */

Thread::Thread(qintptr ID, Master* masterptr, QObject *parent) : QThread(parent)
{
    masterPointer=masterptr;
    this->socketDescriptor = ID;
    compare += 0x1F;
    breaker += 0x1E;
    userPointer = nullptr;
}

// ---------------------------------------
/*Connection of signals and slots, creation of the socket and connection.
 */
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

// ---------------------------

/*The readyRead loop for the server. Separate the command from the data using
 *indexOf(breaker)/indexOf(compare), check which command we just recieved handle
 *it accordingly.
 */

void Thread::readyRead()
{
    
    QByteArray Data = TcpSocket->readAll();
    
    int i;
    
    QString commandName;
    QString inData = Data;
    
    int n = inData.indexOf(breaker); // return the position of the first breaker.
    QString rest;
    
    
    do {
        rest = inData.mid(n+1); //takes everything right of and including position n+1
        inData = inData.left(n); //takes everything left of position n.
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
            cout << "Non-valid command: " << commandName.toStdString() << endl;
            TcpSocket->write("Non-valid command!");
            TcpSocket->waitForBytesWritten(5000);
            cout << socketDescriptor << "Data in: "<< stdInData<<endl;
        }
        
        inData = rest;
        n = inData.indexOf(breaker);
        
    }while (n != -1 ); //run again if there are more breakers.
}

// ---------------------------------------

/*Upon disconnection the disconnect signal will fire and the asscociated slotfunction
 *disconnected will run, deleting the user, the thread and asking the clients to 
 *update their structures.
 */

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

/* Serialization of message then send it to the client.
 */
void Thread::sendMessage(Message messageObject){
    QByteArray array = "/message";
    array += compare; //unit separator
    array += QString::fromStdString(messageObject.getFrom());
    array += compare;
    array += QString::fromStdString(messageObject.getTo());
    array += compare;
    array += QString::fromStdString(messageObject.getMessage());
    array += compare;
    array += QString::fromStdString(messageObject.getServerTime());
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000)){
        try{
            cout << "Couldn't write to client: " << "message" << "from: " << userPointer->getName() <<  endl;
        }catch(...){
        }
    }
}

// -----------------------------------------

/*Serialization of history then send it to the client. The four fields;
 *from to message and servertime will be rebuilt to a message object on the client 
 *side.
 */
void Thread::sendHistory(){
    QByteArray array = "/history";
    array += compare; //unit separator
    unsigned int logSize = userPointer->getParentRoom()->log.size();
    
    if (logSize == 0){
        array += breaker;
    }
    
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
    
    if(!TcpSocket->waitForBytesWritten(5000)){
        try{
            cout << "Couldn't write to client: " << "history" << "from: " << userPointer->getName() <<  endl;
        }catch(...){
        }
    }
    
}

// -----------------------------------------

/*Username taken, ask client to reinitiate, and then disconnect the user.
 */

void Thread::reinitiate(){
    QByteArray array = "/reinitiate";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000)){
        try{
            cout << "Couldn't write to client: " << "reinitiate" << "from: " << userPointer->getName() <<  endl;
        }catch(...){
        }
    }
    disconnected();
}

// -----------------------------------------
/* Ask the client to ask for a new structure.
 */

void Thread::requestStruct() {
    QByteArray array = "/requestStruct";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    
    if(!TcpSocket->waitForBytesWritten(5000)){
        try{
            cout << "Couldn't write to client: " << "requestStruct" << "from: " << userPointer->getName() <<  endl;
        }catch(...){
        }
    }
}
