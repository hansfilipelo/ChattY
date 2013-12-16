#include "logindialog.h"
#include "ui_logindialog.h"
#include "ui_chatwindow.h"
#include "gui.h"

LoginDialog::LoginDialog(ChatWindow* chatPointer,Gui* guiPointer) :
QDialog(nullptr),
ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->inputServer->setPlaceholderText("Example: name.server.com");
    ui->inputName->setPlaceholderText("Example: Name (max 16 characters)");
    ui->inputName->setInputMask("NNNNNNNNNNNNNNNN");
    mainWindow = chatPointer;
    chatGui = guiPointer;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_rejected()
{
    this->close();
    mainWindow->close();
}

void LoginDialog::on_buttonBox_accepted()
{   ui->errorMessage->setText("");
    if (ui->inputName->text()=="User"){
        ui->errorMessage->setText("Name not allowed");
    }
    if (ui->inputServer->text().contains(" ") or ui->inputServer->text()==""){
        ui->errorMessage->setText("Invalid server name");
    }

    else{
        chatGui->createClient(ui->inputName->text(),ui->inputServer->text());
    }

}

void LoginDialog::connected(){
    mainWindow->setName(ui->inputName->text());
    mainWindow->setServer("Server: " + ui->inputServer->text());
    mainWindow->clearHistory();
    this->close();

}

void LoginDialog::userNameTaken(){
    ui->errorMessage->setText("That name is taken");
    ui->inputName->clear();
}

void LoginDialog::noConnection(){
    ui->errorMessage->setText("Server timout. The server is down or invalid address!");
}

void LoginDialog::disconnectedFromServer(){
    ui->errorMessage->setText("Disconnected from server!");
}
