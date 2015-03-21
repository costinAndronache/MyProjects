#include "ChatClient.h"
#include <iostream>
#include "ChatClientListener.h"

ChatClient::ChatClient()
{
    //ctor

    this->connectionON = false;
    this->_listener = NULL;
}

ChatClient::~ChatClient()
{
    //dtor
}

struct ChatClientThData
{
    int socket;
    bool *connectionON;
    ChatClient *theChatClient;
};


void *thread_ReaderThread(void *arg)
{
    ChatClientThData *tData = (ChatClientThData*)arg;
    pthread_detach(pthread_self());

    while(*tData->connectionON == true)
    {
       char buff[2048];
       std::cout<<"Will read from server\n";
       int bytes = read(tData->socket, buff, 2047);

       if(bytes<=0)
       {
           std::cout<<"Will close a socket due to an unknown error or connection closed.\n";
           tData->theChatClient->disconnect();
           return NULL;
       }

       buff[bytes] = '\0';
       std::string s(buff);
       std::cout<<"Just read " << s <<" from the chat server.\n";
       if(s == "QUITLOGOUT")
       {
           return NULL;
       }

       tData->theChatClient->announceListener(s);
    }
    return NULL;
}

bool ChatClient::connectToChatServerWithUserID(char *ipAddress, int port, int userID)
{
    std::cout<<"Will connect to port" << port<<'\n';
    this->socket = createConnectedClientSocket(ipAddress, port);
     int response = -1;

     std::cout<<"Did connect to port: " << port<<'\n';

    int bytes = 0;
    char reply[100];

    if( write(this->socket, &userID, sizeof(int)) > 0)
    {
        std::cout<<"Did send my user id\n";
        bytes = read(this->socket, reply, 10);
        if ( bytes <= 0)
        {
        std::cout<<"Something unexpected happened while sending/receiving the user/reply id to port: " << port <<" -- " << userID <<"\n";
        close(this->socket);
        return false;
        }

        cout<<"Did send and read succesfully! "<<bytes<<"\n";
    }

    reply[bytes] = '\0';

    string resp(reply);

    std::cout<<"Did receive from chat server: " << reply <<'\n';

    if(resp == "NO")
    {
        if(this->_listener != NULL)
            this->_listener->chatClientDidFailToConnect(this);
        return false;
    }

    ChatClientThData *thData = new ChatClientThData;

    this->connectionON = true;
    thData->connectionON = &this->connectionON;
    thData->socket = this->socket;
    thData->theChatClient = this;

    if (pthread_create(&this->readerThreadInfo, NULL, thread_ReaderThread, thData) != 0)
    {
        std::cout <<"Error on creating the reader thread from a chat client. Will exit.\n";
        exit(1);
    }

    if(this->_listener != NULL)
    {
        this->_listener->chatClientDidConnectSuccesfully(this);
    }

    return true;
}

void ChatClient::disconnect()
{
    if(this->connectionON == true)
    {
       std::cout<<"Will disconnect from a chat server.\n";
        this->connectionON = false;
       std::string emptyString = "QUITLOGOUT";
        this->sendMessage(emptyString);
        pthread_join(this->readerThreadInfo, NULL);
        close(this->socket);
    }
}

void ChatClient::announceListener(std::string &message)
{
    std::cout<<"Chat client announcing listener for message: " << message <<'\n';
    if(this->_listener != NULL)
    {
        this->_listener->chatClientDidReceiveMessage(this, message);
    }
}


 bool ChatClient::sendMessage(std::string &message)
{
    if( write(this->socket, message.c_str(), message.length()) <= 0 )
        return false;

    return true;
}
