#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "QString"
#include "QColor"
#include "gui.h"
//

ChatWindow::ChatWindow(Gui* guiPointer) :
    QMainWindow(nullptr),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->parent();
    chatGui = guiPointer;
    debug.open("debug.txt");
    debug<<"test"<<std::endl;
    debug.close();
}

void ChatWindow::receiveMessage(const QString from, const QString to, const QString message, const QString time){

    if(to == name){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText(from +" whispers to you: ");
        ui->messageHistory->setTextColor(Qt::black);

    }
    else if (from == name && to != ""){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText("You whisper to " + to + ": ");
        ui->messageHistory->setTextColor(Qt::black);
    }

    else if (from == name && to == ""){
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText("You say: ");
        ui->messageHistory->setTextColor(Qt::black);

    }
    else {
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(from + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    ui->messageHistory->insertPlainText(message);
    ui->messageHistory->insertPlainText("\n");
}

void ChatWindow::setName(QString inName){
    name = inName;
}

ChatWindow::~ChatWindow()
{
    delete ui;
}


//If sendbutton is pressed display sent from text and message in messagehistory
void ChatWindow::on_sendButton_clicked()
{
    debug<<"innan sendMessage() i send button clicked"<<"\n";
    sendMessage();
    ui->messageInput->clear();
    receiver="root";
    ui->sendButton->setText("Send");

//observera at root är en templösning
}

// send message on return
void ChatWindow::on_messageInput_returnPressed()
{
    debug<<"innan sendMessage() i send returned clicked"<<"\n";
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
void ChatWindow::sendMessage(){
    guiPointer->sendMessage(name,receiver,ui->messageInput->text());
}
void ChatWindow::on_actionBlack_triggered()
{
    ui->messageInput->setStyleSheet("color: black;"
                                    "background-color: grey;"
                                    "selection-color: black;"
                                    "selection-background-color: white");
    ui->treeView->setStyleSheet("color: black;"
                                "background-color: grey;"
                                "selection-color: black;"
                                "selection-background-color: white");
    ui->messageHistory->setStyleSheet("color: black;"
                             "background-color: grey;"
                             "selection-color: black;"
                             "selection-background-color: white");
    this->setStyleSheet("color: white;"
                             "background-color: black;"
                             "selection-color: black;"
                             "selection-background-color: white");
    ui->mainToolBar->setStyleSheet("color: white;"
                               "background-color: black;"
                               "selection-color: black;"
                               "selection-background-color: white");

}

void ChatWindow::on_actionDefault_triggered()
{
    ui->messageInput->setStyleSheet("");
    ui->treeView->setStyleSheet("");
    ui->messageHistory->setStyleSheet("");
    this->setStyleSheet("");
    ui->mainToolBar->setStyleSheet("");

}
