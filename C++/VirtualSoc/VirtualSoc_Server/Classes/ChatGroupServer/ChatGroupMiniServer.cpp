#include "ChatGroupMiniServer.h"

#include <NetworkUtilities/NetworkUtilities.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include<algorithm>

#include "WorkerManager.h"
#include "ChatServersManager.h"

using namespace std;

struct ChatSvThreadData
{
    bool *connectionON;
    ChatGroupMiniServer *chatGroupMiniServer;
    int socket;

};

void *thread_ListeningThread(void *args)
{
    ChatSvThreadData *tData = (ChatSvThreadData*)args;
    pthread_detach(pthread_self());


    printf("Starting to listen on socket %d", tData->socket);

    while(*tData->connectionON == true)
    {
        printf("Accepting:\n");
       int client = accept(tData->socket, NULL, NULL);
       if(client > 0)
       {
           int userID;
           if(read(client, &userID, sizeof(int)) > 0)
           {
               string resp = "YES";
              int response = 0;
              if (tData->chatGroupMiniServer->shouldAcceptSocketWithUserID(userID) == true)
                  {
                      response = 1;
                      std::cout<<"A new client has been accepted to server: " << tData->socket <<".\n";
                      if ( write(client, resp.c_str(), resp.length()) < 0 )
                      {
                          std::cout<<"Could not send confirmation to userID: " << userID<<"\n";
                      }
                      tData->chatGroupMiniServer->connectANewSocket(client);
                  }
                  else
                  {
                      resp = "NO";
                      write(client, resp.c_str(), resp.length());
                      std::cout<<"Rejected the user id " << userID <<" from the chat server socket " << tData->socket<<"\n";
                  }
           }
       }
       else
       {
           std::cout<<"error: "<<strerror(errno)<<"\n";
           break;
       }
    }

    return NULL;
}

ChatGroupMiniServer::ChatGroupMiniServer()
{
    //ctor
}

ChatGroupMiniServer::~ChatGroupMiniServer()
{
    //dtor
}

void ChatGroupMiniServer::workerManagerReportsAllWorkersClosed()
{
    this->connectionON = false;
    pthread_join(this->threadInfo, NULL);
    printf("The chat group server with port %d will close now.", this->port);
    if(this->_manager != NULL)
    {
        this->_manager->removeServerForPort(this->port);
    }

}

int ChatGroupMiniServer::initializeWithListOfUsersAndManagerAndReturnPort(vector<int> &userIDList, ChatServersManager *manager)
{
    this->listOfAcceptedUserIDs = vector<int>(userIDList);
    int port = 2290;
    this->socket = createBindedServerSocketToRandomPort(&port, 5);


    cout<<"This socket is " <<this->socket<<"\n";
    this->workerManager = new WorkerManager;
    this->workerManager->setHostMiniServer(this);

    ChatSvThreadData *tData = new ChatSvThreadData;
    this->connectionON = true;
    tData->connectionON = &this->connectionON;
    tData->chatGroupMiniServer = this;
    tData->socket = this->socket;


    if(pthread_create(&threadInfo, NULL, thread_ListeningThread, tData) != 0)
    {
        printf("Error on creating the listening thread from the mini server. %s", strerror(errno));
        exit(1);
    }

    this->port = port;
    this->_manager = manager;
    return port;
}

void ChatGroupMiniServer::connectANewSocket(int socket)
{
    this->mutex.lock();
    this->workerManager->createNewWorkerForSocket(socket, false);
    this->mutex.unlock();

}

bool ChatGroupMiniServer::shouldAcceptSocketWithUserID(int userID)
{
    vector<int>::iterator it = find(this->listOfAcceptedUserIDs.begin(), this->listOfAcceptedUserIDs.end(), userID);

    if(it != this->listOfAcceptedUserIDs.end() )
    {
        return true;
    }

    return true;
    return false;
}
