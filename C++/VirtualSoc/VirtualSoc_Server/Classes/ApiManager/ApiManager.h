#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <oracle/12.1/client/occi.h>
#include <string>
#include <json/json.h>
#include <map>
#include <ThreadUtilities/Mutex.h>

class ApiManager;

typedef std::string (ApiManager::*RequestProcessingFunction)(Json::Value &value);

class ApiManager
{
    public:

        virtual ~ApiManager();
        static ApiManager* sharedInstance();

        std::string processRequestJSON(std::string &jsonRequest);
    private:
        ApiManager();
        oracle::occi::Environment *env;
        oracle::occi::StatelessConnectionPool *scp;

        std::map<std::string, RequestProcessingFunction> mapOfFunctions;

        std::string getReplyOfLoginRequest(Json::Value &value);
        std::string getReplyOfLogoutRequest(Json::Value &value);
        std::string getReplyOfRegisterRequest(Json::Value &value);

        std::string getReplyOfCreatePostRequest(Json::Value &value);
        std::string getReplyOfPostListRequest(Json::Value &value);
        std::string getReplyOfDeletePostRequest(Json::Value &value);

        std::string getReplyOfGroupListForUserRequest(Json::Value &value);
        std::string getReplyOfGroupListOwnedByUserRequest(Json::Value &value);
        std::string getReplyOfGroupUsersFromGroupRequest(Json::Value &value);
        std::string getReplyOfCreateGroupRequest(Json::Value &value);
        std::string getReplyOfSendGroupInviteRequest(Json::Value &value);
        std::string getReplyOfAcceptGroupInviteRequest(Json::Value &value);
        std::string getReplyOfDeleteGroupRequest(Json::Value &value);

        std::string getReplyOfRetrieveFriendListRequest(Json::Value &value);
        std::string getReplyOfSendFriendRequestRequest(Json::Value &value);
        std::string getReplyOfAcceptFriendRequest(Json::Value &value);
        std::string getReplyOfDeleteFriendRequest(Json::Value &value);

        std::string getReplyOfRetrieveNotificationsList(Json::Value &value);

        std::string getReplyOfStartChatGroupRequest(Json::Value &value);

        std::string getReplyOfRequestUserInfo(Json::Value &value);


        static ApiManager *_sharedInstance;
        static Mutex _sharedMutex;
};

#endif // APIMANAGER_H
