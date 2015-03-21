#ifndef CHATSERVERSMANAGER_H
#define CHATSERVERSMANAGER_H

#include<vector>
#include<map>
#include<ThreadUtilities/Mutex.h>
using namespace std;
class ChatGroupMiniServer;

class ChatServersManager
{
    public:


        int createNewChatGroupServerAndReturnPort(vector<int> &listOfUserIDs);
        void removeServerForPort(int port);
        void extendListOfAcceptedIDsForPort(int port);

        static ChatServersManager *sharedInstance();
        virtual ~ChatServersManager();
    private:
        ChatServersManager();
        map<int, ChatGroupMiniServer*> mapPortToServer;
        Mutex mutex;
        static ChatServersManager *_sharedInstance;
        static Mutex _sharedMutex;
};

#endif // CHATSERVERSMANAGER_H
