#ifndef GUI_H
#define GUI_H
#include <QString>
class NetClient;
class LoginDialog;
class ChatWindow;

/* The Gui class is an abstraction layer between the gui and the net client */

class Gui
{
public:
    Gui();
    void receiveMessage(QString from, QString to, QString message, QString servertime);
    void userNameTaken();
    void connectionTimeOut();
    void connected();
    void createClient(QString inName, QString inAddress);
    void noConnection();
    void sendMessage(QString from, QString to, QString message);
    void updateStruct(QVector<QString> treeStruct);
    void getStruct();
    void receiveHistory(QVector<QString> &historyVector);
    void receiveOldHistory(QVector<QString> &historyVector);
    void getHistory();
    void disconnectedFromServer();

    unsigned int historyCounter;
    
protected:
    NetClient* client = nullptr;
    LoginDialog* loginWindow = nullptr;
    ChatWindow* mainWindow = nullptr;

};

#endif // GUI_H
