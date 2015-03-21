#ifndef CHATGROUPMINISERVER_H
#define CHATGROUPMINISERVER_H

#include <vector>
#include <ThreadUtilities/Mutex.h>
#include <pthread.h>

class WorkerManager;
class ChatServersManager;
using namespace std;

class ChatGroupMiniServer
{
    public:
        ChatGroupMiniServer();

        int initializeWithListOfUsersAndManagerAndReturnPort(vector<int> &listOfUsers, ChatServersManager *manager);
        void addListOfAcceptedUsers(vector<int> &listOfUsers);
        int getSocket(){return this->socket;}
        bool shouldAcceptSocketWithUserID(int userID);
        void workerManagerReportsAllWorkersClosed();
        void connectANewSocket(int socket);

        virtual ~ChatGroupMiniServer();
    protected:
    private:

    ChatServersManager *_manager;
    vector<int> listOfAcceptedUserIDs;
    int socket;
    WorkerManager *workerManager;
    Mutex mutex;
    bool connectionON;
    pthread_t threadInfo;
    int port;
};

#endif // CHATGROUPMINISERVER_H
