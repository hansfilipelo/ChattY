#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "QString"
#include "QColor"
#include "gui.h"
#include <QDebug>
//

ChatWindow::ChatWindow(Gui* guiPointer) :
    QMainWindow(nullptr),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    chatGui = guiPointer;
    smiley= {happyFace,sadFace,straightFace,xdFace,oFace,astronaut,batman,grandpa,ironman,spiderman};

    ui->messageInput->setStyleSheet("white");
    ui->roomTree->setStyleSheet("white");
    ui->messageHistory->setStyleSheet("white");
    this->setStyleSheet("none");
    ui->mainToolBar->setStyleSheet("none");

}

void ChatWindow::receiveMessage(const QString from, const QString to, const QString message, const QString time){
    QString tempString = time;
    ui->messageHistory->moveCursor(QTextCursor::End);
    ui->messageHistory->setTextColor(Qt::black);
    ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");

    if(to == name && from != name){
        lastWhisper=from;
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText(from +" whispers to you: ");
        ui->messageHistory->setTextColor(Qt::black);

    }
    else if (from == name && to != "root" && to !=name){
        ui->messageHistory->setTextColor(Qt::magenta);
        ui->messageHistory->insertPlainText("You whisper to " + to + ": ");
        ui->messageHistory->setTextColor(Qt::black);
    }

    else if (from == name && to == "root"){
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText("You say: ");
        ui->messageHistory->setTextColor(Qt::black);
     }

    else {
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(from + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
    }
    ui->messageHistory->insertHtml(smilieConvert(message));
    ui->messageHistory->insertPlainText("\n");
    ui->messageHistory->moveCursor(QTextCursor::End);
    if(ui->messageHistory->verticalScrollBar()->value() != ui->messageHistory->verticalScrollBar()->maximum())
    {

    }
    else{
        ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
    }

}

void ChatWindow::setName(QString inName){
    name = inName;
}

void ChatWindow::setServer(QString serverName){
    server = serverName;
    ui->roomTree->setHeaderLabel(server);
}

void ChatWindow::updateStruct(QVector<QString> treeStruct){
    ui->roomTree->clear();
    QTreeWidgetItem *treeParent;
    treeParent=addRoot(treeStruct.at(0));
    for (int i=1; i< treeStruct.size(); i++){
        if (treeStruct.at(i)=="User"){
            treeStruct.remove(i);
            while (i < treeStruct.size()){
                addLeaf(treeParent,treeStruct.at(i));
                i++;
            }
        }
        else {
            treeParent=addSubRoot(treeParent,treeStruct.at(i));
        }
    }
    ui->roomTree->expandAll();
}

QTreeWidgetItem* ChatWindow::addRoot(const QString rootName){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->roomTree);
    item->setText(0,rootName);
    ui->roomTree->addTopLevelItem(item);
    return item;

}

QTreeWidgetItem* ChatWindow::addSubRoot(QTreeWidgetItem *parent,const QString subRootName){
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,subRootName);
    parent->addChild(item);
    return item;
}

void ChatWindow::addLeaf(QTreeWidgetItem *parent,const QString leafName){
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,leafName);
    parent->addChild(item);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}
//If sendbutton is pressed display sent from text and message in messagehistory//
void ChatWindow::on_sendButton_clicked()
{
    sendMessage();
    ui->messageInput->clear();
    receiver="root";
    ui->sendButton->setText("Send");

}

// send message on return//
void ChatWindow::on_messageInput_returnPressed()
{
    on_sendButton_clicked();

}


//Slash command control//
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
    if(w=="/r " or w=="/R "){
        to.remove("/r ",Qt::CaseInsensitive);
        receiver=lastWhisper;
        ui->sendButton->setText("To " + receiver);
        ui->messageInput->clear();

    }
}

void ChatWindow::sendMessage(){
    if (ui->messageInput->text()==""){
        return;
    }
    else if(name==receiver){
        whisperToMe(ui->messageInput->text());
    }
    else{
        chatGui->sendMessage(name,receiver,ui->messageInput->text());
    }

}


void ChatWindow::receiveHistory(QVector<QString> &historyVector){
    for(int i = 0;i<historyVector.size(); i+=4){
        QString tempString=historyVector.at(i+3);
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(historyVector.at(i) + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertHtml(smilieConvert(historyVector.at(i+2)));
        ui->messageHistory->insertPlainText("\n");
        ui->messageHistory->moveCursor(QTextCursor::End);

    }
}

void ChatWindow::receiveOldHistory(QVector<QString> &historyVector){
    ui->messageHistory->moveCursor(QTextCursor::Start);
    for(int i = 0;i<historyVector.size(); i+=4){
        QString tempString=historyVector.at(i+3);
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertPlainText(tempString.remove(0,11).remove(5,7)+" | ");
        ui->messageHistory->setTextColor(Qt::blue);
        ui->messageHistory->insertPlainText(historyVector.at(i) + " says: ");
        ui->messageHistory->setTextColor(Qt::black);
        ui->messageHistory->insertHtml(smilieConvert(historyVector.at(i+2)));
        ui->messageHistory->insertPlainText("\n");

    }
    ui->messageHistory->moveCursor(QTextCursor::End);
}

void ChatWindow::getHistory(){
    chatGui->getHistory();
}

void ChatWindow::clearHistory(){
    ui->messageHistory->clear();
}

void ChatWindow::setSmileySize(int size){
    qDebug()<< "tempString3";
    QString sizeString = QString::number(size);
    for (int i=0; i < smiley.size(); i++ ){
        qDebug()<< smiley.size();
        QString tempString = smiley.at(i);
        tempString.chop(23);
        tempString += " width='";
        tempString += sizeString;
        tempString += "' height='" ;
        tempString +=  sizeString;
        tempString += "'>";
        qDebug()<< tempString;
        smiley.replace(i,tempString);
        qDebug()<< "tempString";

    }
}

//---------------------------------Customisation menu-------------------------------//



void ChatWindow::on_actionBlack_triggered()
{
    ui->messageInput->setStyleSheet("background-color: grey;");
    ui->roomTree->setStyleSheet("background-color: grey;");
    ui->messageHistory->setStyleSheet("background-color: grey;");
    this->setStyleSheet("background-color: black;");
}

void ChatWindow::on_actionDefault_triggered()
{
    ui->messageInput->setStyleSheet("white");
    ui->roomTree->setStyleSheet("white");
    ui->messageHistory->setStyleSheet("white");
    this->setStyleSheet("none");
}


void ChatWindow::on_actionChatty_triggered()
{
    setStyleSheet("ChatWindow{border-image:url(:/files/icon/ChattY.png) 0 0 0 0 stretch stretch;}");
    ui->messageHistory->setStyleSheet("background-color: white;");
    QGraphicsOpacityEffect * effect1 = new QGraphicsOpacityEffect(ui->messageHistory);
    effect1->setOpacity(0.8);
    ui->messageHistory->setGraphicsEffect(effect1);
    ui->roomTree->setStyleSheet("background-color: white;");
    QGraphicsOpacityEffect * effect2 = new QGraphicsOpacityEffect(ui->roomTree);
    effect2->setOpacity(0.8);
    ui->roomTree->setGraphicsEffect(effect2);
    QGraphicsOpacityEffect * effect3 = new QGraphicsOpacityEffect(ui->messageInput);
    effect3->setOpacity(0.8);
    ui->messageInput->setGraphicsEffect(effect3);
    ui->sendButton->setStyleSheet("background-color: none;");
}

void ChatWindow::on_actionCezch_triggered()
{
    setStyleSheet("ChatWindow{background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255, 255, 255, 255), stop:0.373979 rgba(255, 255, 255, 255), stop:0.373991 rgba(33, 30, 255, 255), stop:0.624018 rgba(33, 30, 255, 255), stop:0.624043 rgba(255, 0, 0, 255), stop:1 rgba(255, 0, 0, 255));}");
    ui->messageHistory->setStyleSheet("background-color: white;");
    QGraphicsOpacityEffect * effect1 = new QGraphicsOpacityEffect(ui->messageHistory);
    effect1->setOpacity(0.8);
    ui->messageHistory->setGraphicsEffect(effect1);
    ui->roomTree->setStyleSheet("background-color: white;");
    QGraphicsOpacityEffect * effect2 = new QGraphicsOpacityEffect(ui->roomTree);
    effect2->setOpacity(0.8);
    ui->roomTree->setGraphicsEffect(effect2);
    QGraphicsOpacityEffect * effect3 = new QGraphicsOpacityEffect(ui->messageInput);
    effect3->setOpacity(0.8);
    ui->messageInput->setGraphicsEffect(effect3);
    ui->sendButton->setStyleSheet("background-color: none;");
}

void ChatWindow::on_roomTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    receiver = item->text(column);
    ui->sendButton->setText("To " + receiver);
    ui->messageInput->setFocus();
    ui->messageInput->setCursorPosition(0);
}

QString ChatWindow::smilieConvert(const QString inMessage){
    QString messageConv = inMessage.toHtmlEscaped();
    messageConv.replace(":)",smiley.at(0));
    messageConv.replace(":(",smiley.at(1));
    messageConv.replace(":|",smiley.at(2));
    messageConv.replace(":o",smiley.at(3));
    messageConv.replace("xD",smiley.at(4));
    messageConv.replace("astronaut",smiley.at(5));
    messageConv.replace("batman",smiley.at(6));
    messageConv.replace("grandpa",smiley.at(7));
    messageConv.replace("ironman",smiley.at(8));
    messageConv.replace("spiderman",smiley.at(9));
    return messageConv;
}

//-------------Change font menu----------------------------------------------//

void ChatWindow::on_action13_triggered()
{
    QFont f("Geeza Pro", 13);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action15_triggered()
{
    QFont f("Geeza Pro", 15);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action20_triggered()
{
    QFont f("Geeza Pro", 20);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}

void ChatWindow::on_action25_triggered()
{
    QFont f("Geeza Pro", 25);
    ui->messageHistory->setFont(f);
    ui->messageHistory->verticalScrollBar()->setValue(ui->messageHistory->verticalScrollBar()->maximum());
}



//--------------------------------Smiley size menu--------------------------------------//


void ChatWindow::on_action13_2_triggered()
{
    setSmileySize(13);
//     happyFace = "<img src=':files/smilies/happyface.png' width='13' height='13'>";
//     sadFace = "<img src=':files/smilies/sadface.png' width='13' height='13'>";
//     straightFace = "<img src=':files/smilies/straightface.png' width='13' height='13'>";
//     oFace = "<img src=':files/smilies/oface.png' width='13' height='13'>";
//     xdFace = "<img src=':files/smilies/xdface.png' width='13' height='13'>";
}

void ChatWindow::on_action15_2_triggered()
{
    setSmileySize(15);
//    happyFace = "<img src=':files/smilies/happyface.png' width='15' height='15'>";
//    sadFace = "<img src=':files/smilies/sadface.png' width='15' height='15'>";
//    straightFace = "<img src=':files/smilies/straightface.png' width='15' height='15'>";
//    oFace = "<img src=':files/smilies/oface.png' width='15' height='15'>";
//    xdFace = "<img src=':files/smilies/xdface.png' width='15' height='15'>";
}

void ChatWindow::on_action20_2_triggered()
{
    setSmileySize(20);
//    happyFace = "<img src=':files/smilies/happyface.png' width='20' height='20'>";
//    sadFace = "<img src=':files/smilies/sadface.png' width='20' height='20'>";
//    straightFace = "<img src=':files/smilies/straightface.png' width='20' height='20'>";
//    oFace = "<img src=':files/smilies/oface.png' width='20' height='20'>";
//    xdFace = "<img src=':files/smilies/xdface.png' width='20' height='20'>";
//
}

void ChatWindow::on_action25_2_triggered()
{
    setSmileySize(25);
//    happyFace = "<img src=':files/smilies/happyface.png' width='25' height='25'>";
//    sadFace = "<img src=':files/smilies/sadface.png' width='25' height='25'>";
//    straightFace = "<img src=':files/smilies/straightface.png' width='25' height='25'>";
//    oFace = "<img src=':files/smilies/oface.png' width='25' height='25'>";
//    xdFace = "<img src=':files/smilies/xdface.png' width='25' height='25'>";
}

void ChatWindow::on_actionNiklas_triggered()
{
    setSmileySize(99);
//    happyFace = "<img src=':files/smilies/happyface.png' width='120' height='120'>";
//    sadFace = "<img src=':files/smilies/sadface.png' width='120' height='120'>";
//    straightFace = "<img src=':files/smilies/straightface.png' width='120' height='120'>";
//    oFace = "<img src=':files/smilies/oface.png' width='120' height='120'>";
//    xdFace = "<img src=':files/smilies/xdface.png' width='120' height='120'>";
}



//------------------History menu--------------------------------------------//

void ChatWindow::on_actionLoad_history_triggered()
{
    chatGui->getHistory();
}
