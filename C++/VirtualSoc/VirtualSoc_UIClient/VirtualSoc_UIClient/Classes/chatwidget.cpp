#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "userdefaults.h"
#include <json/json.h>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    chatClient.setListener(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::connectToIpAndPort(char *ip, int port)
{
    int userID = 6;//UserDefaults::sharedInstance()->userID;
    this->chatClient.connectToChatServerWithUserID(ip, port, userID);
}

void ChatWidget::chatClientDidFailToConnect(ChatClient *client)
{
    ui->textEdit->append("Failed to connect. The chat group must have closed.");
}

void ChatWidget::chatClientDidReceiveMessage(ChatClient *client, string &message)
{
    Json::Reader reader;
    Json::Value value;

    reader.parse(message, value, false);

    string sender = value["sender"].asString();
    string content = value["content"].asString();
    QString messagem = "[" + QString::fromUtf8(sender.c_str(), sender.length()) + "]: " +
            QString::fromUtf8(content.c_str(), content.length());

    ui->textEdit->append(messagem);
}



void ChatWidget::disconnect()
{
    this->chatClient.disconnect();
}

void ChatWidget::on_sendBtn_clicked()
{
    Json::Value val;
    Json::FastWriter fw;
    string myMessage = ui->lineEdit->text().toStdString();

    val["sender"] = Json::Value(UserDefaults::sharedInstance()->firstName);
    val["content"] = Json::Value(myMessage);

    myMessage = fw.write(val);
    this->chatClient.sendMessage(myMessage);
}

void ChatWidget::chatClientDidConnectSuccesfully(ChatClient *client)
{
    this->ui->textEdit->append("Connected succesfully to chat group.");
}

void ChatWidget::on_disconnectBtn_clicked()
{
    ui->textEdit->append("Disconnecting");
    chatClient.disconnect();
}
