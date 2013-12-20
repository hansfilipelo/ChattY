#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "chatwindow.h"
#include <QDialog>
#include <QString>
#include <iostream>
class Gui;

/*
 Class LoginDialog. Dialog window for connecting to server. Prompts at startup and disconnect.
 */

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
    void userNameTaken();
    void noConnection();
    void disconnectedFromServer();
    ChatWindow* mainWindow;
    Gui* chatGui;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::LoginDialog *ui;


};

#endif // LOGINDIALOG_H
