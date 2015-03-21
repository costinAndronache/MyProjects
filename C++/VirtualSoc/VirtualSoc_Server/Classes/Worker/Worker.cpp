#include "Worker.h"
#include <WorkerManager.h>
#include <WorkerDatabase.h>
#include "CommonConstants.h"
#include "ApiManager.h"

#include <json/json.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <oracle/12.1/client/occi.h>

Worker::Worker(WorkerManager *hostWorkerManager, int socket, bool isForApiManager)
{
    this->hostWorkerManager = hostWorkerManager;
    this->socket = socket;
    this->associatedUserID = -1;

    this->_isForApiManager = isForApiManager;
}

Worker::~Worker()
{
    //dtor
}


void Worker::setAssociatedUserID(int userID)
{
    this->mutex.lock();
     this->associatedUserID = userID;
    this->mutex.unlock();
}

int Worker::getAssociatedUserID()
{
    int result;
    this->mutex.lock();
     result = this->associatedUserID;
    this->mutex.unlock();
    return result;
}

struct ThreadData
{
    bool connectionON;
    Queue<std::string> *messagesToBeReceivedQueue, *messagesToBeSentQueue;
    int socket;
    Worker *theWorker;
};

void *thread_Reader(void *tData)
{
    ThreadData *myData = (ThreadData*)tData;

    pthread_detach(pthread_self());

    char a[100];
    sprintf(a, "for the socket %d, message no. : ", myData->socket);
    int counts = 0;
    while(myData->connectionON)
    {
        char buffer[1025];

        int bytes = read(myData->socket, buffer, 1024);
        if(bytes <= 0)
        {
            printf("\nUnexepected error for the socket with the socket: %d. Will close the connection\n", myData->socket);

            string emptyString("");
            myData->messagesToBeReceivedQueue->push(emptyString);
            myData->messagesToBeSentQueue->push(emptyString);
            close(myData->socket);
            myData->connectionON = false;
            return NULL;
        }

        buffer[bytes] = '\0';
        string s(buffer);
        myData->messagesToBeReceivedQueue->push(s);

        if(s == "QUITLOGOUT")
        {
            printf("Reader thread for %d discovered empty string and will now exit", myData->socket);
            return NULL;
        }

        //std::cout<<"a reader thread for "<<myData->socket<<" pushing message " << s <<'\n';
        //counts++;
        sleep(3);
    }

    return NULL;
}

void *thread_Writer(void *tData)
{
    ThreadData *myData = (ThreadData*)tData;

    pthread_detach(pthread_self());
    while(myData->connectionON)
    {

        std::string message = myData->messagesToBeSentQueue->pop();


        if(myData->theWorker->isForApiManager())
        {
        Json::Value root;
        Json::Reader reader;
        reader.parse(message, root, false);

        std::string method = root[kRequestKey].asString();
        if(method == kRequestLoginKey)
        {
            Json::Value resultParams = root[kResultOfRequestKey];
            int success = resultParams[kSuccessKey].asInt();

            if(success == 1)
            {
                int userID = resultParams[kUserIDKey].asInt();
                WorkerDatabase::sharedInstance()->addNewWorkerForUserID(myData->theWorker, userID);
                cout<<"Just added a new worker in the database for the user id: " << userID<<"\n";
                myData->theWorker->setAssociatedUserID(userID);
            }

        }
        else
            if(method == kRequestLogoutKey)
                {
                    WorkerDatabase::sharedInstance()->removeWorkerForUserID(myData->theWorker->getAssociatedUserID());
                    cout<<"Removed worker for userID from the database: " << myData->theWorker->getAssociatedUserID();
                    }

        }
        else
        {
            cout<<"Writing as a chat server: " <<message<<" from socket " << myData->socket<<"\n";
        }
       write(myData->socket, message.c_str(), message.length());

       cout<<"Did write as a chat server: " <<message<<" from socket "<<myData->socket<<"\n";

        if(message == "QUITLOGOUT")
        {
            cout<<"Writer thread for " << myData->socket<<" has closed.";
            return NULL;
        }
        sleep(1);
        }

    cout<<"Writer thread for " << myData->socket<<" has closed.";
    return NULL;
}

void *thread_Worker(void *tData)
{
    ThreadData *myData = (ThreadData*)tData;

    pthread_detach(pthread_self());
    pthread_t readerThread_t, writerThread_t;
    if(pthread_create(&readerThread_t, NULL, thread_Reader, tData) != 0 || pthread_create(&writerThread_t,NULL, thread_Writer, tData) != 0 )
    {
        std::cout<<"Error on creating the thread which receives from the server ...";
        exit(1);
    }

    int counts = 0;
    while(myData->connectionON == true)
    {
        //std::cout<<"connection for " <<myData->socket<<" still on\n";

        if(myData->messagesToBeReceivedQueue->size() > 0)
       {


        std::string message = myData->messagesToBeReceivedQueue->pop();
        //std::cout<<"worker thread for " << myData->socket <<" extracted: "<<message<<"\n";

        if(message == "QUITLOGOUT")
        {
            myData->connectionON = false;
            myData->messagesToBeSentQueue->push(message);
            break;
        }


        if(myData->theWorker->isForApiManager())
        {
          message = ApiManager::sharedInstance()->processRequestJSON(message);
          myData->messagesToBeSentQueue->push(message);
        }
        else
        {
            //std::cout<<" worker thread for the socket "<< myData->socket<<" broadcasting: " << message<<'\n';
            myData->theWorker->broadcastToOtherWorkers(message);
        }

       }

        sleep(1);
    }

    pthread_join(readerThread_t, NULL);
    pthread_join(writerThread_t, NULL);
    std::cout<<"Reader and writer have returned Worker for "<<myData->socket<<" will exit\n";
    close(myData->socket);
    myData->theWorker->removeFromHost();
    return NULL;

}

void Worker::broadcastToOtherWorkers(std::string &message)
{
    this->hostWorkerManager->sendANewMessageToAllWorkers(message);
}

void Worker::start()
{
    ThreadData *tData = new ThreadData;

    tData->connectionON = true;
    tData->messagesToBeReceivedQueue = &this->messagesReceivedQueue;
    tData->messagesToBeSentQueue = &this->messagesToBeSentQueue;
    tData->socket = this->socket;
    tData->theWorker = this;
    pthread_t workerThread_t;

    if( pthread_create(&workerThread_t, NULL, thread_Worker, tData) != 0 )
    {
        std::cout<<"Could not create worker thread for socket "<<this->socket<<", will now exit.\n";
        exit(1);
    }
}

void Worker::removeFromHost()
{
    if(this->hostWorkerManager == NULL)
    {
        throw "A worker was initialized without a manager!";
    }
    this->hostWorkerManager->removeWorkerForSocket(this->socket);

}

void Worker::appendJSONtoSend(std::string &json)
{
    this->messagesToBeSentQueue.push(json);
}
