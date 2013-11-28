#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "QString"
#include "QColor"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}


//If sendbutton is pressed display sent from text and message in messagehistory
void ChatWindow::on_sendButton_clicked()
{
    QString outMessage;
    outMessage = ui->messageInput->text();
    if(receiver != ""){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText("You whisper to " + receiver + ": ");
        ui->messageHistory->setTextColor(Qt::black);

    }
   else{
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText("You say: ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    ui->messageHistory->insertPlainText(outMessage);
    ui->messageInput->clear();
    ui->messageHistory->insertPlainText("\n");
    //client->sendMessage(outMessage,reciever)
    ui->sendButton->setText("Send");
    receiver="";

}

// send messaeg on return
void ChatWindow::on_messageInput_returnPressed()
{
    on_sendButton_clicked();
}


//whisper control
void ChatWindow::on_messageInput_textEdited(const QString &arg1)
{
    QString to      = arg1;
    QString w       = arg1;
    QString whisper = arg1;
    w.truncate(3);
    whisper.truncate(9);

    if(w == "/w " or w =="/W "){

        to.remove("/w ",Qt::CaseInsensitive);
        if(to.length() > 0 && to.endsWith(" ")){
            to.chop(1);
            receiver = to;
            ui->sendButton->setText("To " + to);
            ui->messageInput->clear();
        }
    }


    if(whisper == "/whisper " or whisper =="/Whisper "){

        to.remove("/whisper ",Qt::CaseInsensitive);
        if(to.length() > 0 && to.endsWith(" ")){
            to.chop(1);
            receiver = to;
            ui->sendButton->setText("To " + to);
            ui->messageInput->clear();
        }
    }
}

void ChatWindow::messageReceived(const QString to, const QString from, const QString message, const QString time){

}
