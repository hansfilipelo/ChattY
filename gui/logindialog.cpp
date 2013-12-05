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
{   if (ui->inputServer->text() == "hfelo.se"){
        ui->inputServer->setText("85.228.199.40");
    }
        chatGui->createClient(ui->inputName->text(),ui->inputServer->text());

    chatGui->createClient(ui->inputName->text(),ui->inputServer->text());
}

void LoginDialog::connected(){
    mainWindow->setName(ui->inputName->text());
    this->close();
}

void LoginDialog::userNameTaken(){
    ui->errorMessage->setText("That name is taken");
    ui->inputName->clear();
}

void LoginDialog::noConnection(){
    ui->errorMessage->setText("Server timout. The server is down or invalid address!");
}
