#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include <map>
#include <ThreadUtilities/Mutex.h>
class Worker;


typedef std::pair<int, Worker*> pSocketWorker;
typedef std::map<int, Worker*> MapSocketWorker;

class ChatGroupMiniServer;

class WorkerManager
{
    public:
        virtual ~WorkerManager();
        void removeWorkerForSocket(int socket);
        void createNewWorkerForSocket(int socket, bool isForApiManager);

        void setHostMiniServer(ChatGroupMiniServer *miniServer){this->hostMiniServer = miniServer; }

        void sendANewMessageToAllWorkers(std::string &message);
        WorkerManager();

    private:
        MapSocketWorker theMap;
        Mutex mutex;
        ChatGroupMiniServer *hostMiniServer;
};

#endif // WORKERMANAGER_H
