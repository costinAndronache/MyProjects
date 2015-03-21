#ifndef APICOMUNICATOR_H
#define APICOMUNICATOR_H

#include <json/json.h>
#include <json/json-forwards.h>
#include <ThreadUtilities/Mutex.h>

#include <string>
#include <map>
#include <Queue.h>
#include <pthread.h>
#include <vector>
using namespace std;


class ApiComunicatorListener
{
    public:
    virtual void didReceiveJSONFromComunicator(string &message) = 0;
};

class ApiComunicator
{
    public:

        bool connectToServerAndPort(char *ip, int port);
        void disconnect();

        void requestLogin(string &username, string &password);
        void requestLogout(int userID);
        void requestRegister(string &username, string &password, string &firstName, string &lastName, string &someInfo, int adminCode);
        void requestPostListFromGroupAndPage(int groupID, int page);
        void requestCreatePost(string &postContents, int forGroupID, int myUserID);
        void requestDeletePost(int postID, int myUserID);
        void requestGetListOfGroupsForUserID(int myUserID);
        void requestGetListOfUsersFromGroup(int groupID);
        void requestCreateGroup(string &groupName, string &groupDescription, int myUserID);
        void requestGetListOfFriendsForUserID(int myUserID);
        void requestGetListOfNotificationsForUserID(int myUserID);
        void requestSendFriendRequest(int myUserID, int toUserID);
        void requestSendGroupInviteRequest(int myGroupID, int toUserID);

        void requestGetListOfOwnedGroupsByUserID(int userID);

        void requestStartChatGroupRequest(int startUserID, std::vector<int> listOfUserIDs);

        void requestAcceptFriendRequest(int myUserID, int fromUserID);
        void requestAcceptGroupInviteRequest(int myUserID, int fromGroupID);

        void requestUserInfo(int userID);

        void setListenerForMethod(ApiComunicatorListener *listener, string &method);
        void removeListenerForMethod(ApiComunicatorListener *listener, string &method);

        void sendMessageForListenersInMethod(string &message, string &method);



        static ApiComunicator *sharedInstance();

        virtual ~ApiComunicator();
    private:
        ApiComunicator();

        map<string, vector<ApiComunicatorListener*> > mapOfListeners;

        int socket;
        static ApiComunicator *_sharedInstance;
        static Mutex _sharedMutex;

        Mutex mutex;
        Queue<string> receivedMessagesQueue;
        bool connected;
        pthread_t readerThreadInfo, workerThreadInfo;

};

#endif // APICOMUNICATOR_H
