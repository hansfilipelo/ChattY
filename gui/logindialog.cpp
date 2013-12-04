#include "logindialog.h"
#include "ui_logindialog.h"
#include "ui_chatwindow.h"
#include "chatwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_rejected()
{
    this->close();
}

void LoginDialog::on_buttonBox_accepted()
{
    this->close();
}
