#include "ApiComunicator.h"
#include <algorithm>
#include <iostream>
#include <NetworkUtilities/NetworkUtilities.h>
#include <CommonConstants.h>

using namespace std;
ApiComunicator::ApiComunicator()
{
    //ctor
}

ApiComunicator::~ApiComunicator()
{
    //dtor
}

ApiComunicator *ApiComunicator::_sharedInstance = NULL;
Mutex ApiComunicator::_sharedMutex = Mutex();

ApiComunicator* ApiComunicator::sharedInstance()
{
    _sharedMutex.lock();
     if(_sharedInstance == NULL)
        _sharedInstance = new ApiComunicator;
     _sharedMutex.unlock();

    return _sharedInstance;
}

void ApiComunicator::setListenerForMethod(ApiComunicatorListener *listener, string &method)
{
    this->mutex.lock();
    cout<<"adding listenr for " << method<<'\n';
    map<string, vector<ApiComunicatorListener*> >::iterator it = this->mapOfListeners.find(method);
    if(it == this->mapOfListeners.end())
    {
        pair<string, vector<ApiComunicatorListener*>> p;
        p.first = method;
        p.second.push_back(listener);
        this->mapOfListeners.insert(p);
    }
    else
    {
        vector<ApiComunicatorListener*> &v = it->second;
        v.push_back(listener);
    }
    this->mutex.unlock();
}

void ApiComunicator::removeListenerForMethod(ApiComunicatorListener *listener, string &method)
{
    //this->mutex.lock();
    map<string, vector<ApiComunicatorListener*> >::iterator it = this->mapOfListeners.find(method);
    if(it != this->mapOfListeners.end())
    {

        vector<ApiComunicatorListener*> v = it->second;

        vector<ApiComunicatorListener*>::iterator fIT = find(v.begin(), v.end(), listener);
        if(fIT != v.end())
        {
            v.erase(fIT);

            std::cout<<"Removing listener for " << method <<'\n';
        }

        it->second = v;
    }
    //this->mutex.unlock();
}

void ApiComunicator::sendMessageForListenersInMethod(string &message, string &method)
{
    this->mutex.lock();

    map<string, vector<ApiComunicatorListener*> >::iterator it = this->mapOfListeners.find(method);
    cout<<"Searching for listeners for " << method<<'\n';
    if(it != this->mapOfListeners.end())
    {
        vector<ApiComunicatorListener*> &v = it->second;
        for(unsigned int i=0; i<v.size(); i++)
        {
            cout<<"Found a listener for method: " << method<<'\n';
            ApiComunicatorListener *listener = v[i];
            listener->didReceiveJSONFromComunicator(message);
        }
    }
    else
    {
        cout<<"didnt find any .. \n";
    }
    this->mutex.unlock();
}


void ApiComunicator::disconnect()
{
    this->connected = false;
    //pthread_join(this->readerThreadInfo, NULL);
    //pthread_join(this->workerThreadInfo, NULL);

    close(this->socket);
}

struct ApiCommThreadData
{
    ApiComunicator *comm;
    Queue<string> *messagesReceivedQueue;
    bool *connected;
    int socket;
};




void *thread_ServerReader(void *args)
{
    cout<<"Started reader \n";
    ApiCommThreadData *tData = (ApiCommThreadData*)args;
    cout<<"Entering while in reader:\n";
    while(tData->connected)
    {
        char buff[2048];
        cout<<"waiting for reading in reader\n";
        int bytes = read(tData->socket, buff, 2049);
        if(bytes<=0)
        {
            Json::Value val;
            val[kRequestKey] = Json::Value(string("Error"));
            Json::FastWriter w;
            string message = w.write(val);
            tData->messagesReceivedQueue->push(message);
            *tData->connected = false;
            return NULL;
        }

        buff[bytes] = '\0';
        string message = string(buff);
        tData->messagesReceivedQueue->push(message);
    }

    return NULL;
}


void *thread_WorkerThread(void *args)
{
    cout<<"Started worker\n";
    ApiCommThreadData *tData = (ApiCommThreadData*)args;
    cout<<"Entering while in writer\n";
    while(tData->connected)
    {
        cout<<"extracting next message in queue\n";
        string nextMessage = tData->messagesReceivedQueue->pop();
        cout<<"did extract a message: "<<nextMessage<<'\n';
        Json::Reader r;
        Json::Value v;
        r.parse(nextMessage, v, false);
        string method = v[kRequestKey].asString();
        if(method == "Error")
        {
            *tData->connected = false;
            cout<<"Error encountered: zzz\n";
            *tData->connected = false;
            return NULL;

        }

        tData->comm->sendMessageForListenersInMethod(nextMessage, method);
    }

    return NULL;
}

bool ApiComunicator::connectToServerAndPort(char *ip, int port)
{
    this->socket = createConnectedClientSocket(ip, port);
    this->connected = true;

    ApiCommThreadData *tData = new ApiCommThreadData;
    tData->comm = this;
    tData->connected = &this->connected;
    tData->socket = this->socket;
    tData->messagesReceivedQueue = &this->receivedMessagesQueue;



    if(pthread_create(&this->readerThreadInfo, NULL, thread_ServerReader, tData) != 0 ||
       pthread_create(&this->workerThreadInfo, NULL, thread_WorkerThread, tData) != 0)
    {
        cout<<"Could not create the threads from the api communicator..";
    }

    return true;
}

/*   Actual useful methods */




void ApiComunicator::requestLogin(string &username, string &password)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUsernameKey] = Json::Value(username);
    params[kPasswordKey] = Json::Value(password);
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestLoginKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestRegister(string &username, string &password, string &firstName, string &lastName, string &someInfo,
                                     int adminCode)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUsernameKey] = Json::Value(username);
    params[kPasswordKey] = Json::Value(password);
    params[kFirstNameKey] = Json::Value(firstName);
    params[kLastNameKey] = Json::Value(lastName);
    params[kSomeInfoKey] = Json::Value(someInfo);
    params["kAdminCode"] = Json::Value(adminCode);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestRegisterKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request register ...";
    }
}

void ApiComunicator::requestCreatePost(string &postContents, int forGroupID, int myUserID)
{

        Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kPostContentKey] = Json::Value(postContents);
    params[kPostOwnerIDKey] = Json::Value(myUserID);
    params[kPostGroupIDKey] = Json::Value(forGroupID);
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestCreatePostKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestCreateGroup(string &groupName, string &description, int myUserID)
{
        Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kGroupDescriptionKey] = Json::Value(description);
    params[kGroupNameKey] = Json::Value(groupName);
    params[kGroupOwnerIDKey] = Json::Value(myUserID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestCreateGroupKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestPostListFromGroupAndPage(int groupID, int page)
{
        Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kPostGroupIDKey] = Json::Value(groupID);
    params[kPageNoKey] = Json::Value(page);
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestPostListKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}


void ApiComunicator::requestDeletePost(int postID, int myUserID)
{

        Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kPostIDKey] = Json::Value(postID);
    params[kPostOwnerIDKey] = Json::Value(myUserID);
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestDeletePostKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestGetListOfFriendsForUserID(int myUserID)
{

        Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUserIDKey] = Json::Value(myUserID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestFriendListKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestGetListOfGroupsForUserID(int myUserID)
{
            Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUserIDKey] = Json::Value(myUserID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestGroupListKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }

    cout<<"Did call group list refresh\n";

}


void ApiComunicator::requestSendFriendRequest(int myUserID, int toUserID)
{

    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kFirstUserIDKey] = Json::Value(myUserID);
    params[kSecondUserIDKey] = Json::Value(toUserID);
    params[kRequestKey] = Json::Value(kRequestSendFriendRequestKey);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestSendFriendRequestKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestUserInfo(int userID)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUserIDKey] = Json::Value(userID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestUserInfo);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestAcceptFriendRequest(int myUserID, int toUserID)
{
            Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kFirstUserIDKey] = Json::Value(toUserID);
    params[kSecondUserIDKey] = Json::Value(myUserID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestAcceptFriendRequestKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestSendGroupInviteRequest(int myGroupID, int toUserID)
{
                Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kGroupIDKey] = Json::Value(myGroupID);
    params[kSecondUserIDKey] = Json::Value(toUserID);
    params[kRequestKey] = Json::Value(kRequestSendGroupInviteRequestKey);
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestSendGroupInviteRequestKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}

void ApiComunicator::requestAcceptGroupInviteRequest(int myUserID, int fromGroupID)
{
                Json::Value root;
    Json::Value params;
    Json::FastWriter fw;

    params[kUserIDKey] = Json::Value(myUserID);
    params[kGroupIDKey] = Json::Value(fromGroupID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestAcceptGroupInviteRequestKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
    }
}
void ApiComunicator::requestGetListOfUsersFromGroup(int groupID)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;


    params[kGroupIDKey] = Json::Value(groupID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestGroupUsersFromGroupKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
        }
}

void ApiComunicator::requestGetListOfOwnedGroupsByUserID(int userID)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;


    params[kUserIDKey] = Json::Value(userID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestOwnedGroups);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
        }
}

void ApiComunicator::requestStartChatGroupRequest(int startUserID, std::vector<int> listOfUserIDs)
{
    Json::Value root;
    Json::Value params;
    Json::Value array;
    Json::FastWriter fw;


    params[kStartUserIDKey] = Json::Value(startUserID);

    for(int i=0; i<listOfUserIDs.size(); i++)
    {
        Json::Value aUserID(listOfUserIDs[i]);
        array.append(aUserID);
    }

    params[kGroupUserIDListKey] = array;
    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kStartChatGroupRequest);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login start chat group ...";
     }
}

void ApiComunicator::requestGetListOfNotificationsForUserID(int myUserID)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;


    params[kUserIDKey] = Json::Value(myUserID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestNotificationsListKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request login ...";
        }
}

void ApiComunicator::requestLogout(int userID)
{
    Json::Value root;
    Json::Value params;
    Json::FastWriter fw;


    params[kUserIDKey] = Json::Value(userID);

    root[kParametersKey] = params;
    root[kRequestKey] = Json::Value(kRequestLogoutKey);

    string req = fw.write(root);

    if(write(this->socket, req.c_str(), req.length()) < 0)
    {
        cout<<"Could not send request logout ...";
        }
}
