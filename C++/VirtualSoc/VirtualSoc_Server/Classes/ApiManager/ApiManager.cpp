#include "ApiManager.h"
#include "CommonConstants.h"
#include <iostream>
#include <oracle/12.1/client/occi.h>
#include "ChatServersManager.h"
#include "WorkerDatabase.h"
#include "Worker/Worker.h"

using namespace std;
using namespace oracle;

typedef pair<string, RequestProcessingFunction> pSRpf;
ApiManager::ApiManager()
{
    string user = "COSTIN";
    string passwd = "mingming";
    string db = "localhost:1521/xe";

    this->env = oracle::occi::Environment::createEnvironment(oracle::occi::Environment::THREADED_MUTEXED);
    this->scp = env->createStatelessConnectionPool(user, passwd, db, 10, 0, 1);

    pSRpf p = pSRpf(string(kRequestLoginKey), &ApiManager::getReplyOfLoginRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestLogoutKey), &ApiManager::getReplyOfLogoutRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestRegisterKey), &ApiManager::getReplyOfRegisterRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestPostListKey), &ApiManager::getReplyOfPostListRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestCreatePostKey), &ApiManager::getReplyOfCreatePostRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestDeletePostKey), &ApiManager::getReplyOfDeletePostRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestGroupListKey), &ApiManager::getReplyOfGroupListForUserRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestGroupUsersFromGroupKey), &ApiManager::getReplyOfGroupUsersFromGroupRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestCreateGroupKey), &ApiManager::getReplyOfCreateGroupRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestFriendListKey), &ApiManager::getReplyOfRetrieveFriendListRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestNotificationsListKey), &ApiManager::getReplyOfRetrieveNotificationsList);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestSendFriendRequestKey), &ApiManager::getReplyOfSendFriendRequestRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestAcceptFriendRequestKey), &ApiManager::getReplyOfAcceptFriendRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestSendGroupInviteRequestKey), &ApiManager::getReplyOfSendGroupInviteRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestAcceptGroupInviteRequestKey), &ApiManager::getReplyOfAcceptGroupInviteRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestUserInfo), &ApiManager::getReplyOfRequestUserInfo);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kRequestOwnedGroups), &ApiManager::getReplyOfGroupListOwnedByUserRequest);
    this->mapOfFunctions.insert(p);

    p = pSRpf(string(kStartChatGroupRequest), &ApiManager::getReplyOfStartChatGroupRequest);
    this->mapOfFunctions.insert(p);

}

ApiManager::~ApiManager()
{
    this->env->terminateStatelessConnectionPool(this->scp);
    occi::Environment::terminateEnvironment(this->env);
}

ApiManager* ApiManager::_sharedInstance = NULL;
Mutex ApiManager::_sharedMutex = Mutex();

ApiManager* ApiManager::sharedInstance()
{
    _sharedMutex.lock();
    if(_sharedInstance == NULL)
    {
        _sharedInstance = new ApiManager;
    }
    _sharedMutex.unlock();

    return _sharedInstance;
}

string ApiManager::getReplyOfLoginRequest(Json::Value &value)
{
    cout<<"called " << kRequestLoginKey<<" for " << value[kUsernameKey].asString() <<" \n";

    Json::Value resultValue;
    try
    {
    oracle::occi::Connection *conn = this->scp->getConnection();
    oracle::occi::Statement *stmt;
    string queryToVerify =
    "SELECT COUNT(*) FROM users WHERE LTRIM(RTRIM(username, ' '), ' ') = :1 AND LTRIM(RTRIM(password, ' '), ' ') = :2";

    stmt = conn->createStatement(queryToVerify);


    string username, password;
    username = value[kUsernameKey].asString();
    password = value[kPasswordKey].asString();

    cout<<"Provided username: " << username<<" and password: "<<password<<"\n";

    stmt->setString(1, username );
    stmt->setString(2, password );

    cout<<"\nFirstExtraction ok!\n";

    oracle::occi::ResultSet *rs = stmt->executeQuery();

    rs->next();
    int exists = rs->getInt(1);
    if(exists == 1)
    {
        resultValue[kSuccessKey] = Json::Value(1);
        cout<<"\nDidSetSuccess\n";
        stmt->closeResultSet(rs);

        string queryToExtract = "SELECT userid, firstname, lastname FROM users WHERE \
        LTRIM(RTRIM(username, ' '), ' ') = :1 AND LTRIM(RTRIM(password, ' '), ' ') = :2 ";
        stmt->setSQL(queryToExtract);
        stmt->setString(1, username );
        stmt->setString(2, password );

        rs = stmt->executeQuery();
        rs->next();
        resultValue[kUserIDKey] = Json::Value( rs->getInt(1));
        resultValue[kFirstNameKey] = Json::Value(rs->getString(2));
        resultValue[kLastNameKey] = Json::Value( rs->getStream(3));
        stmt->closeResultSet(rs);


        string queryToUpdate = " UPDATE users SET isloggedin = 1 WHERE LTRIM(RTRIM(username, ' '), ' ') = :1 AND LTRIM(RTRIM(password, ' '), ' ') = :2";
        stmt->setSQL(queryToUpdate);
        stmt->setString(1, username );
        stmt->setString(2, password );

        stmt->executeUpdate();

    }
    else
    {
        cout<<"\nWillsetsuccess0\n";
        resultValue[kSuccessKey] = Json::Value(0);
        cout<<"\ndidsetsuccess0\n";
    }
      conn->terminateStatement(stmt);
      this->scp->releaseConnection(conn);
    }
    catch(oracle::occi::SQLException &ex)
    {
        Json::Value errorDetails = Json::Value(ex.what());
        resultValue[kErrorDetailsKey] = errorDetails;
        resultValue[kSuccessKey] = Json::Value(0);
    }

    Json::FastWriter fastWriter;
    cout<<"Will write result value\n";
    return fastWriter.write(resultValue);
}

string ApiManager::getReplyOfLogoutRequest(Json::Value &value)
{
    cout<<"called logout for " <<value[kUserIDKey].asInt()<<'\n';
    int userID = value[kUserIDKey].asInt();

    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);

    try
    {
        occi::Connection *conn = this->scp->getConnection();
        string queryToUpdate = " UPDATE users SET isloggedin = 0 WHERE userid = :1";
        occi::Statement *stmt = conn->createStatement(queryToUpdate);
        stmt->setSQL(queryToUpdate);
        stmt->setInt(1, userID);
        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);

    }catch(occi::SQLException &ex)
    {
        Json::Value errorDetails = Json::Value(ex.what());
        resultValue[kErrorDetailsKey] = errorDetails;
        resultValue[kSuccessKey] = Json::Value(0);
    }

    Json::FastWriter fastWriter;
    return fastWriter.write(resultValue);

}

string ApiManager::getReplyOfRegisterRequest(Json::Value& value)
{
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);

    cout<<"called register for " << value[kUsernameKey].asString()<<"\n";
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        string queryToVerify ="SELECT COUNT(*) FROM users WHERE LTRIM(RTRIM(username, ' '), ' ') = :1";
        occi::Statement *stmt = conn->createStatement(queryToVerify);
        stmt->setString(1, value[kUsernameKey].asString());

        occi::ResultSet *rs = stmt->executeQuery();
        rs->next();

        int alreadyExistent = rs->getInt(1);
        if(alreadyExistent == 1)
        {
            resultValue[kSuccessKey] = Json::Value(0);
            resultValue[kErrorDetailsKey] = Json::Value("That username is already registered.");
            stmt->closeResultSet(rs);
        }
        else
        {

        stmt->closeResultSet(rs);
        string queryToUpdate = "INSERT INTO USERS(FIRSTNAME, LASTNAME, USERNAME, SOMEINFO, PASSWORD, ISADMIN) \
        VALUES(:1, :2, :3, :4, :5, :6)";

        int adminCode = value["kAdminCode"].asInt();
        if(adminCode == 1994)
        {
            adminCode = 1;
        }
        else
        {
            adminCode = 0;
        }

        stmt->setSQL(queryToUpdate);
        stmt->setString(1, value[kFirstNameKey].asString());
        stmt->setString(2, value[kLastNameKey].asString());
        stmt->setString(3, value[kUsernameKey].asString());
        stmt->setString(4, value[kSomeInfoKey].asString());
        stmt->setString(5, value[kPasswordKey].asString());
        stmt->setInt(6, adminCode);

        stmt->executeUpdate();
        }

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);

    }catch(occi::SQLException &ex)
    {
        Json::Value errorDetails = Json::Value(ex.what());
        resultValue[kErrorDetailsKey] = errorDetails;
        resultValue[kSuccessKey] = Json::Value(0);
    }

    Json::FastWriter fastWriter;
    return fastWriter.write(resultValue);
}

string ApiManager::getReplyOfPostListRequest(Json::Value &value)
{
    int pageNo = value[kPageNoKey].asInt();
    int groupID = value[kPostGroupIDKey].asInt();
    int numOfRows = 10; //max 10 per page

    cout<<"Asked for posts from " << groupID <<" with pageNo "<<pageNo<<'\n';
    Json::Value resultValue;

    try
    {
    oracle::occi::Connection *conn = this->scp->getConnection();
    oracle::occi::Statement *stmt;
    string an = "SELECT *\
FROM (\
  SELECT b.*, ROWNUM rn\
  FROM (\
    SELECT content, ownerid, datepublished, postid\
    FROM POSTS\
    WHERE groupid = :1\
    ORDER BY datepublished DESC\
  ) b\
  WHERE ROWNUM <= :2  ) WHERE rn >= :3";

    stmt = conn->createStatement(an);

    stmt->setInt(1, groupID);
    stmt->setInt(2, (pageNo+1)*numOfRows + 1);
    stmt->setInt(3, (pageNo-1)*numOfRows +1);



    oracle::occi::ResultSet *rs = stmt->executeQuery();

    Json::Value arrayOfPosts;
    Json::Value aPost;

    while(rs->next())
    {
        aPost[kPostOwnerIDKey] = Json::Value( rs->getInt(2) );
        aPost[kPostContentKey] = Json::Value( rs->getString(1) );
        occi::Date aDate = rs->getDate(3);
        string fmt = "dd-mm-yyyy";
        aPost[kPostDatePublishedKey] = aDate.toText(fmt);

        aPost[kPostIDKey] = Json::Value( rs->getInt(4));

        arrayOfPosts.append(aPost);
    }

      resultValue[kSuccessKey] = Json::Value(1);
      resultValue[kPostListKey] = arrayOfPosts;

      stmt->closeResultSet(rs);
      conn->terminateStatement(stmt);
      this->scp->releaseConnection(conn);
    }
    catch(oracle::occi::SQLException &ex)
    {
        Json::Value errorDetails = Json::Value(ex.what());
        resultValue[kErrorDetailsKey] = errorDetails;
        resultValue[kSuccessKey] = Json::Value(0);
    }

    Json::FastWriter fastWriter;
    return fastWriter.write(resultValue);
}

string ApiManager::getReplyOfCreatePostRequest(Json::Value &value)
{
    string postContent = value[kPostContentKey].asString();
    int groupID = value[kPostGroupIDKey].asInt();
    int userID = value[kPostOwnerIDKey].asInt();
    occi::Date date = occi::Date::getSystemDate(this->env);

    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;

        string queryToUpdate = "INSERT INTO posts(content, ownerid, groupid, datepublished) VALUES(:1, :2, :3, :4)";
        stmt = conn->createStatement(queryToUpdate);
        stmt->setString(1, postContent);
        stmt->setInt(2, userID);
        stmt->setInt(3, groupID);
        stmt->setDate(4, date);


        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        scp->releaseConnection(conn);
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfDeletePostRequest(Json::Value &value)
{
    int postID = value[kPostIDKey].asInt();
    int ownerID = value[kPostOwnerIDKey].asInt();

    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string queryToCheckOwnership = "SELECT COUNT(*) FROM posts p, users u WHERE u.userid = p.ownerid AND u.userid = :1 AND p.postid = :2";
        stmt = conn->createStatement(queryToCheckOwnership);
        stmt->setInt(1, ownerID);
        stmt->setInt(2, postID);

        rs = stmt->executeQuery();

        rs->next();
        int ownershipIsTrue = rs->getInt(1);
        stmt->closeResultSet(rs);

        if(ownershipIsTrue == 0)
        {
            //The user doesn't own the post but he might be an admin
            string queryToCheckAdmin = "SELECT isadmin FROM users WHERE userid = :1";
            stmt->setSQL(queryToCheckAdmin);
            stmt->setInt(1, ownerID);

            rs = stmt->executeQuery();
            rs->next();

            int isAdmin = rs->getInt(1);
            stmt->closeResultSet(rs);
            if( isAdmin == 1)
            {
                //Issue the delete
                string queryToDelete = "DELETE FROM posts WHERE postid = :1";
                stmt->setSQL(queryToDelete);
                stmt->setInt(1, postID);

                stmt->executeUpdate();
            }
            else
            {
                resultValue[kSuccessKey] = Json::Value(0);
                resultValue[kErrorDetailsKey] = Json::Value("You don't own the post. Only admins can delete unowned posts.");
            }
        }
        else
        {
            cout<<"Issuing the delete: \n";
            //Issue the delete
                string queryToDelete = "DELETE FROM posts WHERE postid = :1";
                stmt->setSQL(queryToDelete);
                stmt->setInt(1, postID);

                stmt->executeUpdate();
        }

        conn->terminateStatement(stmt);
        scp->releaseConnection(conn);
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfGroupListForUserRequest(Json::Value &value)
{
    int userID = value[kUserIDKey].asInt();
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *con = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string query = "SELECT g.* FROM groups g, groupmemberships gm WHERE gm.userid = :1 AND gm.groupid = g.groupid";
        stmt = con->createStatement(query);
        stmt->setInt(1, userID);
        rs = stmt->executeQuery();

        Json::Value arrayOfGroups;
        Json::Value aGroup;

        while(rs->next())
        {
            aGroup[kGroupIDKey] = Json::Value(rs->getInt(1));
            aGroup[kGroupOwnerIDKey] = Json::Value(rs->getInt(2));
            aGroup[kGroupNameKey] = Json::Value(rs->getString(3));
            aGroup[kGroupDescriptionKey] = Json::Value(rs->getString(4));

            arrayOfGroups.append(aGroup);
        }

        stmt->closeResultSet(rs);
        con->terminateStatement(stmt);
        scp->releaseConnection(con);
        resultValue[kGroupListKey] = arrayOfGroups;
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(1);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfRequestUserInfo(Json::Value &value)
{
    int userID = value[kUserIDKey].asInt();
    Json::FastWriter fw;
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string query = "SELECT  firstname, lastname, someinfo FROM users WHERE userid = :1";
        stmt = conn->createStatement(query);
        stmt->setInt(1, userID);

        rs = stmt->executeQuery();

        if(rs->next())
        {
            resultValue[kFirstNameKey] = Json::Value(rs->getString(1));
            resultValue[kLastNameKey] = Json::Value(rs->getString(2));
            resultValue[kSomeInfoKey] = Json::Value(rs->getString(3));
        }
        else
        {
            resultValue[kSuccessKey] = Json::Value(0);
            resultValue[kErrorDetailsKey] = Json::Value("No such user with an id found..");
        }

        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);
    }catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    return fw.write(resultValue);
}

string ApiManager::getReplyOfGroupUsersFromGroupRequest(Json::Value &value)
{
    int groupID = value[kGroupIDKey].asInt();
    Json::Value resultValue;
    resultValue[kSuccessKey]  = Json::Value(1);

    cout<<"For groupid = " <<groupID<<"\n";
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        if(groupID != -1)
        {string query = "SELECT u.userid, u.firstname, u.lastname, u.someinfo\
                        FROM users u, groupmemberships gm\
                        WHERE u.userid = gm.userid AND gm.groupid = :1";

        stmt = conn->createStatement(query);
        stmt->setInt(1, groupID);
        }
        else
        {
            stmt=conn->createStatement("SELECT u.userid, u.firstname, u.lastname, u.someinfo FROM users u");
        }
        rs = stmt->executeQuery();

        Json::Value arrayOfUSers;
        Json::Value aUser;

        while(rs->next())
        {
            aUser[kUserIDKey] = Json::Value(rs->getInt(1));
            aUser[kFirstNameKey] = Json::Value(rs->getString(2));
            aUser[kLastNameKey] =  Json::Value(rs->getString(3));
            aUser[kSomeInfoKey] = Json::Value(rs->getString(4));

            arrayOfUSers.append(aUser);
        }

        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);
        scp->releaseConnection(conn);

        resultValue[kGroupUsersList] = arrayOfUSers;
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    string s = fw.write(resultValue);
    cout<<"result of group users for " << groupID<<" is: \n" << s;
    return s;
}

string ApiManager::getReplyOfCreateGroupRequest(Json::Value &value)
{
    int ownerID = value[kGroupOwnerIDKey].asInt();
    string groupName = value[kGroupNameKey].asString();
    string description = value[kGroupDescriptionKey].asString();
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);

    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        //First we check if the name is already taken

        string queryToVerify = "SELECT COUNT(*) FROM groups WHERE RTRIM(groupname, ' ') = :1";
        stmt = conn->createStatement(queryToVerify);
        stmt->setString(1, groupName);

        rs = stmt->executeQuery();
        rs->next();

        int alreadyExists = rs->getInt(1);
        stmt->closeResultSet(rs);

        if(alreadyExists == 1)
        {
            resultValue[kSuccessKey] = Json::Value(0);
            resultValue[kErrorDetailsKey] = Json::Value("That group name is already taken");
        }
        else
        {
            string queryToInsert = "INSERT INTO groups(ownerid, groupname, description) VALUES(:1, :2, :3)";
            stmt->setSQL(queryToInsert);
            stmt->setInt(1, ownerID);
            stmt->setString(2, groupName);
            stmt->setString(3, description);
            stmt->executeUpdate();
        }

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfRetrieveFriendListRequest(Json::Value &value)
{
    int userID = value[kUserIDKey].asInt();
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *con = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string query = "SELECT u.userid, u.firstname, u.lastname, u.someinfo, u.isloggedin \
                        FROM users u, friendships fr\
                        WHERE (fr.firstuserid = :1 AND fr.seconduserid = u.userid) OR (fr.seconduserid = :2 AND fr.firstuserid = u.userid)";

        stmt = con->createStatement(query);
        stmt->setInt(1, userID);
        stmt->setInt(2, userID);

        rs = stmt->executeQuery();
        Json::Value arrayOfFriends;
        Json::Value aFriend;
        while(rs->next())
        {
            aFriend[kUserIDKey] = Json::Value(rs->getInt(1));
            aFriend[kFirstNameKey] = Json::Value(rs->getString(2));
            aFriend[kLastNameKey] = Json::Value(rs->getString(3));
            aFriend[kSomeInfoKey] = Json::Value(rs->getString(4));
            aFriend[kIsLoggedInKey] = Json::Value(rs->getInt(5));

            arrayOfFriends.append(aFriend);
        }

        stmt->closeResultSet(rs);
        con->terminateStatement(stmt);
        this->scp->releaseConnection(con);

        resultValue[kFriendsListKey] = arrayOfFriends;
    }
    catch(occi::SQLException &e)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(e.what());
    }

    Json::FastWriter fw;
    string s = fw.write(resultValue);

    cout<<"Friend list for the user id: " << userID<<'\n' << s <<"\n";

    return s;
}

string ApiManager::getReplyOfRetrieveNotificationsList(Json::Value &value)
{
    int forUserID = value[kUserIDKey].asInt();

    cout<<"Notifications for userid " << forUserID<<"\n";
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string query = "SELECT contents FROM notifications WHERE targeteduserid = :1";
        stmt = conn->createStatement(query);
        stmt->setInt(1, forUserID);

        rs = stmt->executeQuery();

        Json::Value notificationsArray;
        while(rs->next())
        {
            string jsonNotif = rs->getString(1);
            notificationsArray.append(Json::Value(jsonNotif));
        }

        stmt->closeResultSet(rs);
        string queryToDelete = "DELETE FROM notifications WHERE targeteduserid = :1";
        stmt->setSQL(queryToDelete);
        stmt->setInt(1, forUserID);

        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);

        resultValue[kNotificationsList] = notificationsArray;
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfSendFriendRequestRequest(Json::Value &value)
{
    int toUserID = value[kSecondUserIDKey].asInt();
    Json::FastWriter fw;
    string contents = fw.write(value);
    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);

    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        string queryToInset = "INSERT INTO notifications(targeteduserid, contents) VALUES(:1, :2)";
        stmt=conn->createStatement(queryToInset);

        stmt->setInt(1, toUserID);
        stmt->setString(2, contents);

        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    return fw.write(resultValue);
}

string ApiManager::getReplyOfSendGroupInviteRequest(Json::Value &value)
{
    return this->getReplyOfSendFriendRequestRequest(value);
}

string ApiManager::getReplyOfAcceptFriendRequest(Json::Value &value)
{
    int firstUserID = value[kFirstUserIDKey].asInt();
    int secondUserID = value[kSecondUserIDKey].asInt();

    Json::Value resultValue;
    resultValue[kSuccessKey] = Json::Value(1);

    try
    {

        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        string queryToAddFriendship = "INSERT INTO friendships(firstuserid, seconduserid) VALUES(:1, :2)";
        stmt = conn->createStatement(queryToAddFriendship);
        stmt->setInt(1, firstUserID);
        stmt->setInt(2, secondUserID);

        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(0);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}

string ApiManager::getReplyOfAcceptGroupInviteRequest(Json::Value &value)
{
    int userID = value[kUserIDKey].asInt();
    int groupID = value[kGroupIDKey].asInt();
    Json::Value result;
    result[kSuccessKey] = Json::Value(1);
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        string queryToInsert = "INSERT INTO GROUPMEMBERSHIPS(groupid, userid) VALUES(:1, :2)";

        stmt = conn->createStatement(queryToInsert);
        stmt->setInt(1, groupID);
        stmt->setInt(2, userID);

        stmt->executeUpdate();

        conn->terminateStatement(stmt);
        this->scp->releaseConnection(conn);
    }catch(occi::SQLException &ex)
    {
        result[kSuccessKey] = Json::Value(0);
        result[kErrorDetailsKey] = Json::Value(ex.what());

    }

    Json::FastWriter w;
    return w.write(result);
}

string ApiManager::getReplyOfStartChatGroupRequest(Json::Value &value)
{

    Json::FastWriter writer;
    Json::Value rvalue;

    int port;
    int startUserID;
    vector<int> arrayOfUsers;

    startUserID = value[kStartUserIDKey].asInt();

    cout<<"Did receive start chat group request: startID = "<<startUserID<<'\n';

    Json::Value listOfUsers = value[kGroupUserIDListKey];
    for(unsigned int i=0; i<listOfUsers.size(); i++)
        arrayOfUsers.push_back( listOfUsers[i].asInt() );

    arrayOfUsers.push_back(startUserID);
    port = ChatServersManager::sharedInstance()->createNewChatGroupServerAndReturnPort(arrayOfUsers);

    cout<<"Did receive a new port: " << port<<'\n';

    arrayOfUsers.pop_back();


    rvalue[kRequestKey] = Json::Value(string(kAcceptChatGroupRequest));
    Json::Value params;
    params[kChatServerPortKey] = Json::Value(port);
    rvalue[kResultOfRequestKey] = params;

    std::string messageToTheUsers = writer.write(rvalue);

    for(unsigned int i=0; i< arrayOfUsers.size(); i++)
    {
        int aUSerID = arrayOfUsers[i];
        Worker *associatedWorker = WorkerDatabase::sharedInstance()->getWorkerForUserID(aUSerID);
        if(associatedWorker!=NULL)
        {
            cout<<"Found a worker for userID: " <<aUSerID<<'\n';
            associatedWorker->appendJSONtoSend(messageToTheUsers);
        }
    }

    cout<<"Message to the users: " << messageToTheUsers<<"\n";
    return writer.write(params);
}

string ApiManager::getReplyOfGroupListOwnedByUserRequest(Json::Value &value)
{
    Json::Value resultValue;
    int userID = value[kUserIDKey].asInt();
    try
    {
        occi::Connection *conn = this->scp->getConnection();
        occi::Statement *stmt;
        occi::ResultSet *rs;

        string query = "SELECT g.* FROM groups g WHERE g.ownerid = :1";
        stmt = conn->createStatement(query);
        stmt->setInt(1, userID);
        rs = stmt->executeQuery();

        Json::Value arrayOfGroups;
        Json::Value aGroup;

        while(rs->next())
        {
            aGroup[kGroupIDKey] = Json::Value(rs->getInt(1));
            aGroup[kGroupOwnerIDKey] = Json::Value(rs->getInt(2));
            aGroup[kGroupNameKey] = Json::Value(rs->getString(3));
            aGroup[kGroupDescriptionKey] = Json::Value(rs->getString(4));

            arrayOfGroups.append(aGroup);
        }

        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);
        scp->releaseConnection(conn);
        resultValue[kGroupListKey] = arrayOfGroups;
    }
    catch(occi::SQLException &ex)
    {
        resultValue[kSuccessKey] = Json::Value(1);
        resultValue[kErrorDetailsKey] = Json::Value(ex.what());
    }

    Json::FastWriter fw;
    return fw.write(resultValue);
}
string ApiManager::processRequestJSON(string& jsonRequest)
{

    cout<<"Did receive json request: " <<jsonRequest<<'\n';
    Json::Reader reader;
    Json::Value reqValue;
    if (reader.parse(jsonRequest, reqValue, false) == false )
    {
        throw "Error on parsing: " + jsonRequest;
    }

    string requestMethod = reqValue[kRequestKey].asString();

    cout<<"The request method is " << requestMethod<<'\n';

    std::map<std::string, RequestProcessingFunction>::iterator it = this->mapOfFunctions.find(requestMethod);

    if( it == this->mapOfFunctions.end())
    {
        throw "Could not find a function for the method " + requestMethod;
    }

    cout<<"So far, found a function to handle\n";

    RequestProcessingFunction fn = it->second;
    Json::Value params = reqValue[kParametersKey];
    string result = (this->*fn)(params);
    Json::Value resultValue;


    Json::Value theResult;
    Json::Reader r;
    r.parse(result, theResult, false);

    resultValue[kResultOfRequestKey] = theResult;
    resultValue[kRequestKey] = Json::Value(requestMethod);


    Json::FastWriter fw;

    //return result;

    return fw.write(resultValue);
}
