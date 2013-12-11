#include "gui.h"
#include "../client/NetClient.h"
#include "chatwindow.h"
#include "logindialog.h"

Gui::Gui()
{

    mainWindow = new ChatWindow(this);
    loginWindow = new LoginDialog(mainWindow, this);
    mainWindow->show();
    loginWindow->setModal(true);
    loginWindow->show();
}

// --------------------------

void Gui::receiveMessage(QString from, QString to, QString message, QString servertime) {
    mainWindow->receiveMessage(from, to, message, servertime);
}

void Gui::connected(){
    loginWindow->connected();
}

void Gui::createClient(QString inName, QString inAddress){
    delete client;
    client = new NetClient(inName, inAddress, this);
    client->start();
}

void Gui::userNameTaken(){
    loginWindow->userNameTaken();
}

void Gui::noConnection(){
    loginWindow->noConnection();
}

void Gui::sendMessage(QString from, QString to, QString message){
    client->sendMessage(from,to,message);
}

void Gui::updateStruct(QVector<QString> treeStruct){
    mainWindow->updateStruct(treeStruct);
}

void Gui::getStruct(){
    mainWindow->updateStruct(client->getStruct());
}

void Gui::receiveHistory(QVector<QString> &historyVector){
    mainWindow->receiveHistory(historyVector);
}
