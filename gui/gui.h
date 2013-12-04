#ifndef GUI_H
#define GUI_H
#include "logindialog.h"
#include "chatwindow.h"
#include <QString>

class NetClient;

class Gui
{
public:
    Gui(); //Skall skapa ett NetClient objekt
    void receiveMessage(QString from, QString to, QString message, QString servertime);
    void userNameTaken();
    void connectionTimeOut();
    void connected();
    // void Gui::updateStruct(vector);
protected:
    NetClient* client;
    LoginDialog* loginWindow;
    ChatWindow* mainWindow;
};

#endif // GUI_H
