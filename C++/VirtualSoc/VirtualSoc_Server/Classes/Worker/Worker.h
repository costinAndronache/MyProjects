#ifndef WORKER_H
#define WORKER_H

#include <Queue.h>
#include <string>
#include <ThreadUtilities/Mutex.h>

class WorkerManager;
class Worker
{
    public:
        Worker(WorkerManager *host, int socket, bool isForApiManager);
        ~Worker();
        void start();
        void appendJSONtoSend(std::string &json);
        void setAssociatedUserID(int userID);
        int getAssociatedUserID();

        bool isForApiManager(){return this->_isForApiManager;}
        void removeFromHost();

        void broadcastToOtherWorkers(std::string &message);
    private:
    bool _isForApiManager;
    WorkerManager *hostWorkerManager;
    Queue<std::string> messagesReceivedQueue;
    Queue<std::string> messagesToBeSentQueue;
    int socket;
    int associatedUserID;
    Mutex mutex;

};

#endif // WORKER_H
