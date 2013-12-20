/*
 FILNAMN: 		NetClient.cc
 PROGRAMMERARE:	hanel742, eriek984, jened502, tobgr602, niker917, davha227
 SKAPAD DATUM:	2013-11-19
 BESKRIVNING:
 */

#include "NetClient.h"
#include "../gui/gui.h"

using namespace std;
/*Creationg of NetClient object, with specifying of compare and breaker, our network
 *data and call separators. Takes a pointer to the class GUI, the abstraction layer
 *between the graphical classes and the network.
 */
NetClient::NetClient(QString username, QString inAddress, Gui* myGui, QObject *parent) : QObject(parent){
    
    guiPointer = myGui;
    name=username;
    address=inAddress;
    compare += 0x1F;
    breaker +=0x1E;
}

// ---------------------------------------------

/*Connect the slots to the corresponding signals so that when the signals fire the
 *slot functions will run. Do a DNS lookup, for IP from dns name. connect to the host,
 *on port 40001.
 */

void NetClient::start(){
    TcpSocket = new QTcpSocket(this);
    
    connect(TcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(TcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    
    QHostInfo info = QHostInfo::fromName(address);
    
    if (info.addresses().size() == 0){
        guiPointer->noConnection();
    }
    else{
        TcpSocket->connectToHost(info.addresses().at(0),quint16(40001));
        if(!TcpSocket->waitForConnected(1000)){
            guiPointer->noConnection();
        }
    }
}


//------Slots---------

/* When a connection is established we send the server the initiate command, appending
 *our desire name. all traffic is sent via arrays, and are always deserialized from/to
 *strings.
 */

void NetClient::connected(){
    QByteArray array = "/initiate";
    array += compare; //unit separator
    array += name;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::disconnected(){
    guiPointer->disconnectedFromServer();
    
}

// --------readyRead------------------

/*
 *The main readloop of our network.
 *Whenever data is available readyread is fired, and thus runs. 
 *Here we deserialize data into a commandname and a rest. 
 *Due to how our protocol for sending data is specified a valid command must
 *contain atleast one breaker sign. If this sign is not present we save the
 *current inData and add it together with the new indata when readyread is 
 *fired again. Not doing this, will result in, whenever you send "large" amounts
 *of data over the network the data could be cut and not be a valid command/data set. 
 */

void NetClient::readyRead(){
    
    QString inData = "";
    
    if( not(incompleteCommand.isEmpty())){
        inData = incompleteCommand;
        incompleteCommand = "";
    }
    QByteArray Data = TcpSocket->readAll();
    
    QString commandName = "";
    inData += Data;
    QString rest = "";
    int n = inData.indexOf(breaker);    //indexOf returns the position of the first
                                        //occurence of the char breaker.
    int i;                              //-1 if not present.
    
    if(inData.indexOf(breaker) == -1 ){ //No breaker, save data for later.
        incompleteCommand = inData;
        return;
    }
    
    do {
        
        rest = inData.mid(n+1);       //Take everything right of and including i+1
        inData = inData.left(n);      //Take everything left of index i.
        i = inData.indexOf(compare);
        commandName = inData.left(i);
        
        inData = inData.mid(i+1);
        
        QString temp = inData;
        string stdInData = temp.toStdString();
        
        // Check which command that's supposed to run
        if (commandName == "/reinitiate") {
            guiPointer->userNameTaken();        //reinitiate sent from server, i.e.
            break;                              //username already taken
        }
        
        else if ( commandName == "/userAccepted") {
            guiPointer->connected();
        }
        
        else if (commandName == "/history") {
            handleHistory(inData);
        }
        
        else if (commandName == "/oldHistory") {
            handleOldHistory(inData);
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
            //Flushing data if an unknown command is read.
            cout << "Unknown command: " << endl;
            inData = "";
            commandName = "";
            incompleteCommand = "";
            return;
        }
        
        inData = rest;
        n = inData.indexOf(breaker);
        commandName = "";
        
    }while (n != -1 ); // do this as long as there is atleast one breaker.
}

// ---------------------------------------------

void NetClient::sendMessage(QString from, QString to, QString message){
    QByteArray array = "/message";
    array += compare; //unit separator
    array += from;
    array += compare;
    array += to;
    array += compare;
    array += message;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

void NetClient::setName(QString inName) {
    name=inName;
}

//-----------------------------------------------
//Helpfunctions


/* Asks server for structure.
 */
void NetClient::getStruct(){
    QByteArray array = "/structure";
    array += compare;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}

//----------------------------------------------


/*All handleFunctions in NetClient are deserialization of data sent from server
 *usually they also pass the data along to the gui.
 */

/*Server asks client to ask for an updated structure.
 *This happens when a new user connects.
 */


// ---------------------------------------------

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
    
    //Send message to Gui
    guiPointer->receiveMessage(from, to, contents, dateTime);
    
}

// ---------------------------------------------

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
    //send history to the gui.
    guiPointer->receiveHistory(history);
}

// ---------------------------------------------

void NetClient::handleRequestStruct(){
    getStruct();
}
//-----------------------------------------------

void NetClient::handleOldHistory(QString inData){
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
    guiPointer->receiveOldHistory(history);
}

// ---------------------------------------------

void NetClient::handleStructure(QString inData){
    QVector<QString> output;
    int i = inData.indexOf(compare);
    
    while(i  != -1){
        //Create vector output, containing room content structure
        QString data = inData.left(i);
        inData = inData.mid(i+1);
        output.push_back(data);
        
        i = inData.indexOf(compare);
    }
    
    output.push_back(inData);
    
    guiPointer->updateStruct(output);
    
}

// ---------------------------------------------


/*Ask server for histroy, daysback number of days ago.
 */
void NetClient::getHistory(unsigned int daysBack) {
    QString temp;
    string daysBackString = to_string(daysBack);
    
    temp = QString::fromStdString(daysBackString);
    
    QByteArray array = "/oldHistory";
    array += compare; //unit separator
    array += temp;
    array += breaker;
    
    TcpSocket->write(array);
    TcpSocket->waitForBytesWritten(1000);
}


