#include "ChatServersManager.h"
#include "ChatGroupMiniServer.h"
ChatServersManager::ChatServersManager()
{
    //ctor
}

ChatServersManager::~ChatServersManager()
{
    //dtor
}

int ChatServersManager::createNewChatGroupServerAndReturnPort(vector<int> &listOfUSerIDs)
{

    ChatGroupMiniServer *chatMiniServer = new ChatGroupMiniServer;
    int port = chatMiniServer->initializeWithListOfUsersAndManagerAndReturnPort(listOfUSerIDs, this);

    std::pair<int, ChatGroupMiniServer*> p(port, chatMiniServer);

    this->mutex.lock();
    this->mapPortToServer.insert(p);
    this->mutex.unlock();

    return port;
}

void ChatServersManager::removeServerForPort(int port)
{

    map<int, ChatGroupMiniServer*>::iterator it = this->mapPortToServer.find(port);
    if(it != this->mapPortToServer.end())
    {
        ChatGroupMiniServer *sv = it->second;
        this->mutex.lock();
        this->mapPortToServer.erase(port);
        this->mutex.unlock();
        delete sv;
    }

}

ChatServersManager *ChatServersManager::_sharedInstance = NULL;
Mutex ChatServersManager::_sharedMutex = Mutex();

ChatServersManager *ChatServersManager::sharedInstance()
{
    _sharedMutex.lock();
    if(_sharedInstance == NULL)
        _sharedInstance = new ChatServersManager();
    _sharedMutex.unlock();

    return _sharedInstance;
}
