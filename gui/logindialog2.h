#ifndef LOGINDIALOG2_H
#define LOGINDIALOG2_H

#include <QDialog>

namespace Ui {
class LoginDialog2;
}

class LoginDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog2(QWidget *parent = 0);
    ~LoginDialog2();

private:
    Ui::LoginDialog2 *ui;
};

#endif // LOGINDIALOG2_H
