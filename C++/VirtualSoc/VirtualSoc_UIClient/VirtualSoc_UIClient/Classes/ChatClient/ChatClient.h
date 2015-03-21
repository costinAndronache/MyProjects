#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <ThreadUtilities/Mutex.h>
#include <NetworkUtilities/NetworkUtilities.h>
#include <Queue.h>

#include<string>
#include<pthread.h>

using namespace std;

class ChatClientListener;

class ChatClient
{
    public:
        ChatClient();
        virtual ~ChatClient();
        bool sendMessage(std::string &message);
        void disconnect();
        void setListener(ChatClientListener *listener){this->_listener = listener;}
        bool connectToChatServerWithUserID(char *ipAddress, int port, int userID);
        void announceListener(std::string &message);

    protected:
    private:
    int socket;
    bool connectionON;
    ChatClientListener *_listener;

    pthread_t readerThreadInfo;
};

#endif // CHATCLIENT_H
