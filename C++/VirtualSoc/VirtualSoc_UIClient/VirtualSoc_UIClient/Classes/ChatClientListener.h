#ifndef CHATCLIENTLISTENER_H
#define CHATCLIENTLISTENER_H

#include <string>

class ChatClient;

class ChatClientListener
{
    public:
        ChatClientListener();
        virtual ~ChatClientListener();
        virtual void chatClientDidReceiveMessage(ChatClient *client, std::string &message);
        virtual void chatClientDidConnectSuccesfully(ChatClient *client);
        virtual void chatClientDidFailToConnect(ChatClient *client);

    protected:
    private:
};

#endif // CHATCLIENTLISTENER_H
