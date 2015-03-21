#ifndef USERDEFAULTS_H
#define USERDEFAULTS_H

#include<string>
#include<ThreadUtilities/Mutex.h>
#include<vector>
#include<json/json.h>
#include<CommonConstants.h>

struct Group
{
    int groupID;
    int ownerID;
    std::string groupName;
    std::string groupDescription;

    static Group groupFromJsonValue(Json::Value &val)
    {
        Group g;

        g.groupID = val[kGroupIDKey].asInt();
        g.groupName = val[kGroupNameKey].asString();
        g.groupDescription = val[kGroupDescriptionKey].asString();
        g.ownerID = val[kGroupOwnerIDKey].asInt();
        return g;
    }

    static Group publicGroup()
    {
        Group g;
        g.groupID = -1;
        g.ownerID = 1;
        g.groupName = "Public";
        g.groupDescription = "This is the public group.";
        return g;
    }

};

struct User
{
    int userID;
    std::string firstName, lastName, someInfo;
    bool isLoggedIn;
    static User friendFromJsonValue(Json::Value &val)
    {
        User aFriend;
        aFriend.userID = val[kUserIDKey].asInt();
        aFriend.firstName = val[kFirstNameKey].asString();
        aFriend.lastName = val[kLastNameKey].asString();
        aFriend.isLoggedIn = val[kIsLoggedInKey].asInt();
        aFriend.someInfo = val[kSomeInfoKey].asString();

        return aFriend;
    }
};

struct Post
{
    int postID;
    int ownerID;
    std::string contents;

    static Post postFromJsonValue(Json::Value &val)
    {
        Post post;
        post.contents = val[kPostContentKey].asString();
        post.postID = val[kPostIDKey].asInt();
        post.ownerID = val[kPostOwnerIDKey].asInt();
        return post;
    }
};

struct Request
{
    bool isFriendRequest;
    int senderID;

    static Request requestFromJson(Json::Value &val)
    {
        Request r;
        std::string method = val[kRequestKey].asString();
        if(method == kRequestSendFriendRequestKey)
        {
            r.isFriendRequest = true;
            r.senderID = val[kFirstUserIDKey].asInt();
        }
        else
        {
            r.isFriendRequest = false;
            r.senderID = val[kGroupIDKey].asInt();
        }

        return r;
    }
};

class UserDefaults
{
public:

    std::string username, firstName, lastName, someInfo;
    int userID;
    bool isLoggedIn;

    std::vector<Group> groupList;
    std::vector<Group> myGroupsList;
    std::vector<User> myFriendsList;


    static UserDefaults *sharedInstance();


private:
    UserDefaults();
    static UserDefaults *_sharedInstance;
    static Mutex _sharedMutex;
};

#endif // USERDEFAULTS_H
