#include "ChatClientListener.h"
#include <iostream>

ChatClientListener::ChatClientListener()
{
    //ctor
}

ChatClientListener::~ChatClientListener()
{
    //dtor
}

void ChatClientListener::chatClientDidReceiveMessage(ChatClient *chatClient, std::string &message)
{
    std::cout<<"\n[Server]: "<<message<<"\n";
}

void ChatClientListener::chatClientDidConnectSuccesfully(ChatClient *client)
{
    std::cout <<"Hurray, chat client connected.";
}

void ChatClientListener::chatClientDidFailToConnect(ChatClient *client)
{
    std::cout <<"Client failed zzz...";
}
