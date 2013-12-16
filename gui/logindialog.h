#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "chatwindow.h"
#include <QDialog>
#include <QString>
#include <iostream>
class Gui;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(ChatWindow* chatPointer, Gui* guiPointer);
    ~LoginDialog();
    void connected();
    ChatWindow* mainWindow;
    Gui* chatGui;
    void userNameTaken();
    void noConnection();
    
    void disconnectedFromServer();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::LoginDialog *ui;


};

#endif // LOGINDIALOG_H
