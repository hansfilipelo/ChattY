#include "logindialog2.h"
#include "ui_logindialog2.h"

LoginDialog2::LoginDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog2)
{
    ui->setupUi(this);
}

LoginDialog2::~LoginDialog2()
{
    delete ui;
}
