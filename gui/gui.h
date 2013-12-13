#ifndef GUI_H
#define GUI_H
#include <QString>
class NetClient;
class LoginDialog;
class ChatWindow;

class Gui
{
public:
    Gui(); //Skall skapa ett NetClient objekt
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
    // void Gui::updateStruct(vector);
    
    // Disconnected from server
    void disconnectedFromServer();
    
protected:
    NetClient* client = nullptr;
    LoginDialog* loginWindow = nullptr;
    ChatWindow* mainWindow = nullptr;
};

#endif // GUI_H
