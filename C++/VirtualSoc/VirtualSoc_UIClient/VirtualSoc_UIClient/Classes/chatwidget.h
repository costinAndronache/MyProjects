#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "ChatClient.h"
#include "ChatClientListener.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget, public ChatClientListener
{
    Q_OBJECT
    
public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();
    
    void chatClientDidReceiveMessage(ChatClient *client, string &message);
    void chatClientDidFailToConnect(ChatClient *client);
    void chatClientDidConnectSuccesfully(ChatClient *client);
    void connectToIpAndPort(char *ip, int port);
    void disconnect();
private slots:
    void on_sendBtn_clicked();

    void on_disconnectBtn_clicked();

private:
    Ui::ChatWidget *ui;
    ChatClient chatClient;
};

#endif // CHATWIDGET_H
