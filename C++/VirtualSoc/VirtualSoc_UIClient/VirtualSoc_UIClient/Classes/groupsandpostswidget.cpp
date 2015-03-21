#include "groupsandpostswidget.h"
#include "ui_groupsandpostswidget.h"
#include "CommonConstants.h"

GroupsAndPostsWidget::GroupsAndPostsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupsAndPostsWidget)
{
    ui->setupUi(this);
    currentSelectedGroup = Group::publicGroup();
    currentSelectedUser.userID = myLastSelectedFriend.userID = -1;
    myLastSelectedGroup.groupID = -1;
    selectedRequest.senderID = -1;
    currentSelectedPost.postID = -1;

    defaults = UserDefaults::sharedInstance();

    string method = kAcceptChatGroupRequest;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    listener = NULL;
}

GroupsAndPostsWidget::~GroupsAndPostsWidget()
{
    delete ui;
}

void GroupsAndPostsWidget::didReceiveJSONFromComunicator(string &message)
{
    Json::Reader reader;
    Json::Value root;
    Json::Value result;

    reader.parse(message, root, false);

    string method = root[kRequestKey].asString();
    result = root[kResultOfRequestKey];

    if(method == kRequestPostListKey)
    {
        this->setupPostListWithJson(result);
    }

    if(method == kRequestGroupListKey)
    {
        this->setupGroupListWithJson(result);
    }

    if(method == kRequestCreatePostKey)
    {
        int succes = result[kSuccessKey].asInt();
        if(succes == 1)
        {
            ui->label_5->setText("Successfully created a new post");
        }
        else
           {
            ui->label_5->setText("Sorry, an error occured");
        }
    }

    if(method == kRequestGroupUsersFromGroupKey)
    {
        this->setupListOfGroupUsersWithJson(result);
    }

    if(method == kRequestFriendListKey)
    {
        this->setupMyFriendsListWithJson(result);
    }

    if(method == kRequestOwnedGroups)
    {
        this->setupMyGroupsListWithJson(result);
    }

    if(method == kRequestSendFriendRequestKey || method == kRequestSendGroupInviteRequestKey)
    {
        int succes = result[kSuccessKey].asInt();
        QString qs = succes == 1 ? "Succesfully sent." : "An error occured";
        ui->inviteStatusLabel->setText(qs);
    }

    if(method == kRequestNotificationsListKey)
    {
        this->setupNotificationsListWithJson(result);
    }

    if(method == kRequestAcceptFriendRequestKey || method == kRequestAcceptGroupInviteRequestKey)
    {
        int succes = result[kSuccessKey].asInt();

        QString qs = succes == 1 ? "Succes" : "Failed";
        ui->confirmLabel->setText(qs);
    }


    if(method == kRequestCreateGroupKey)
    {
        int succes = result[kSuccessKey].asInt();
        if(succes == 1)
        {
            ui->groupCreateStatusLabel->setText("Succesfully created");
        }
        else
        {
            string details =result[kErrorDetailsKey].asString();
            QString qs = QString :: fromUtf8(details.c_str(), details.length());
            ui->groupCreateStatusLabel->setText(qs);
        }
    }

    if(method == kRequestDeletePostKey)
    {
        int succes = result[kSuccessKey].asInt();
        if(succes == 1)
        {
            ui->deletePostStatusLabel->setText("Succesfully deleted");
        }
        else
        {
            string details =result[kErrorDetailsKey].asString();
            QString qs = QString :: fromUtf8(details.c_str(), details.length());
            ui->deletePostStatusLabel->setText(qs);
        }
    }

    if(method == kStartChatGroupRequest)
    {
        int port = result[kChatServerPortKey].asInt();
        ui->chatWidget->disconnect();
        ui->chatWidget->connectToIpAndPort("127.0.0.1", port);
    }

    if(method == kAcceptChatGroupRequest)
    {
        ui->groupCreateStatusLabel->setText("Did receive start chat group request");
        int port = result[kChatServerPortKey].asInt();
        ui->chatWidget->disconnect();
        ui->chatWidget->connectToIpAndPort("127.0.0.1", port);
        return;
    }
    ApiComunicator::sharedInstance()->removeListenerForMethod(this, method);
}

void GroupsAndPostsWidget::setupGroupListWithJson(Json::Value &val)
{
    ui->groupListWidget->clear();
    groupList.clear();
    UserDefaults *defaults = UserDefaults::sharedInstance();

    defaults->groupList.clear();

    Group pub = Group::publicGroup();

    defaults->groupList.push_back(pub);
    this->groupList.push_back(pub);
    QString qs = QString::fromUtf8(pub.groupName.c_str(), pub.groupName.length());
    ui->groupListWidget->addItem(qs);

    Json::Value groupArray = val[kGroupListKey];
    for(int i=0; i<groupArray.size(); i++)
    {
        Group g = Group::groupFromJsonValue(groupArray[i]);
        QString qs = QString::fromUtf8(g.groupName.c_str(), g.groupName.length());
        ui->groupListWidget->addItem(qs);

        this->groupList.push_back(g);
        defaults->groupList.push_back(g);
    }

}

void GroupsAndPostsWidget::setupPostListWithJson(Json::Value &val)
{
    ui->postListWidget->clear();
    Json::Value postsArray = val[kPostListKey];
    this->postList.clear();
    for(int i=0; i<postsArray.size(); i++)
    {
        Post p = Post::postFromJsonValue(postsArray[i]);
        QString qs = QString::fromUtf8(p.contents.c_str(), p.contents.length());
        ui->postListWidget->addItem(qs);
        this->postList.push_back(p);
    }

}



void GroupsAndPostsWidget::on_refreshGroupListBtn_clicked()
{
    string method = kRequestGroupListKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestGetListOfGroupsForUserID(defaults->userID);
}

void GroupsAndPostsWidget::on_groupListWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
        Group g = groupList[currentRow];
        QString qs = QString::fromUtf8(g.groupDescription.c_str(), g.groupDescription.length());
        ui->groupDescriptionLabel->setText(qs);

        ui->userInfoWidget->populateWithInfoAboutUserID(g.ownerID);

        currentSelectedGroup = g;
    }
}

void GroupsAndPostsWidget::on_postListRefreshBtn_clicked()
{
    string method = kRequestPostListKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);

    int fromGroupID = this->currentSelectedGroup.groupID;

    ApiComunicator::sharedInstance()->requestPostListFromGroupAndPage(fromGroupID, 1);
}

void GroupsAndPostsWidget::on_postListWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
        currentSelectedPost = this->postList[currentRow];
        QString qs = QString::fromUtf8(currentSelectedPost.contents.c_str(), currentSelectedPost.contents.length());
        ui->postContentLabel->setText(qs);
        ui->userInfoWidget->populateWithInfoAboutUserID(currentSelectedPost.ownerID);
    }
}

void GroupsAndPostsWidget::on_sendPostBtn_clicked()
{
    QString contents = ui->postContentTextEdit->toPlainText();
    string mContents = contents.toStdString();

    if(mContents.length() == 0)
    {
        ui->label_5->setText("Please make sure the text isnt empty!");
    }
    else
    {
        string method = kRequestCreatePostKey;
        ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
        ApiComunicator::sharedInstance()->requestCreatePost(mContents, currentSelectedGroup.groupID, defaults->userID);
    }
}

void GroupsAndPostsWidget::setupListOfGroupUsersWithJson(Json::Value &val)
{
    ui->groupUsersList->clear();
    usersFromGroupList.clear();
    Json::Value array = val[kGroupUsersList];
    for(int i=0; i<array.size(); i++)
    {
        User u = User::friendFromJsonValue(array[i]);
        usersFromGroupList.push_back(u);
        QString firstName = QString::fromUtf8(u.firstName.c_str(), u.firstName.length());
        QString lastName = QString::fromUtf8(u.lastName.c_str(), u.lastName.length());
        QString qs = firstName+ " " + lastName;

        ui->groupUsersList->addItem(qs);
    }
}

void GroupsAndPostsWidget::setupMyFriendsListWithJson(Json::Value &val)
{
    ui->myFriendList->clear();
    myFriendsList.clear();
    Json::Value array = val[kFriendsListKey];
    for(int i=0; i<array.size(); i++)
    {
        User u = User::friendFromJsonValue(array[i]);
        if(u.isLoggedIn == true)
        {
           myFriendsList.push_back(u);
        QString firstName = QString::fromUtf8(u.firstName.c_str(), u.firstName.length());
        QString lastName = QString::fromUtf8(u.lastName.c_str(), u.lastName.length());
        QString qs = firstName+ " " + lastName;

        ui->myFriendList->addItem(qs);
        }
    }

    if(array.size() == 0)
    {
        ui->myFriendList->addItem("None online.");
    }
}
void GroupsAndPostsWidget::setupMyGroupsListWithJson(Json::Value &val)
{
    ui->myGroupsList->clear();
    myGroupList.clear();
    UserDefaults *defaults = UserDefaults::sharedInstance();

    Json::Value groupArray = val[kGroupListKey];
    for(int i=0; i<groupArray.size(); i++)
    {
        Group g = Group::groupFromJsonValue(groupArray[i]);
        QString qs = QString::fromUtf8(g.groupName.c_str(), g.groupName.length());
        ui->myGroupsList->addItem(qs);

        myGroupList.push_back(g);
    }
}

void GroupsAndPostsWidget::on_listGroupUsersBtn_clicked()
{
    string method = kRequestGroupUsersFromGroupKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestGetListOfUsersFromGroup(currentSelectedGroup.groupID);
}

void GroupsAndPostsWidget::on_pushButton_3_clicked()
{
    //refresh friend list button

    string method = kRequestFriendListKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestGetListOfFriendsForUserID(defaults->userID);
}

void GroupsAndPostsWidget::on_groupUsersList_currentRowChanged(int currentRow)
{
    if(currentRow>=0)
    {
        currentSelectedUser = usersFromGroupList[currentRow];
        ui->userInfoWidget->populateWithInfoAboutUserID(currentSelectedUser.userID);
    }
}

void GroupsAndPostsWidget::on_myFriendList_currentRowChanged(int currentRow)
{
    if(currentRow>=0)
    {
        myLastSelectedFriend = myFriendsList[currentRow];
        ui->userInfoWidget->populateWithInfoAboutUserID(myLastSelectedFriend.userID);
    }
}

void GroupsAndPostsWidget::on_myGroupListBtn_clicked()
{
    string method = kRequestOwnedGroups;

    ApiComunicator::sharedInstance()->setListenerForMethod(this,method);
    ApiComunicator::sharedInstance()->requestGetListOfOwnedGroupsByUserID(defaults->userID);
}

void GroupsAndPostsWidget::on_myGroupsList_currentRowChanged(int currentRow)
{
    if(currentRow >=0)
    {
        myLastSelectedGroup = myGroupList[currentRow];
        QString qs = QString::fromUtf8(myLastSelectedGroup.groupDescription.c_str(),
                                       myLastSelectedGroup.groupDescription.length());

        ui->groupDescriptionLabel->setText(qs);
    }
}

void GroupsAndPostsWidget::on_sendFriendRequest_clicked()
{
    if(currentSelectedUser.userID == -1)
    {
        ui->inviteStatusLabel->setText("Please select a user");
        return;
    }

    string method = kRequestSendFriendRequestKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestSendFriendRequest(defaults->userID, currentSelectedUser.userID);
}

void GroupsAndPostsWidget::on_groupInviteBtn_clicked()
{
    if(currentSelectedUser.userID == -1)
    {
        ui->inviteStatusLabel->setText("Please select a user");
        return;
    }

    if(myLastSelectedGroup.groupID == -1)
    {
        ui->inviteStatusLabel->setText("Please select a group of your own");
    }

    string method = kRequestSendGroupInviteRequestKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestSendGroupInviteRequest(myLastSelectedGroup.groupID, currentSelectedUser.userID);
}

void GroupsAndPostsWidget::setupNotificationsListWithJson(Json::Value &val)
{
    Json::Value array = val[kNotificationsList];
    Json::Value v;
    Json::Reader r;

    ui->notificationsList->clear();
    myRequestList.clear();

    for(int i=0; i<array.size(); i++)
    {
        string notif = array[i].asString();
        r.parse(notif, v, false);
        Request req = Request::requestFromJson(v);
        QString qs = req.isFriendRequest? "Friend request" : "Group invite request";
        ui->notificationsList->addItem(qs);

        myRequestList.push_back(req);
    }

    if(array.size() == 0)
    {
        ui->notificationsList->addItem("No notifications.");
    }
}

void GroupsAndPostsWidget::on_pushButton_clicked()
{
    string method = kRequestNotificationsListKey;

    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestGetListOfNotificationsForUserID(defaults->userID);
}

void GroupsAndPostsWidget::on_pushButton_2_clicked()
{
    if(selectedRequest.senderID == -1)
    {
        ui->confirmLabel->setText("Please select a notification");
        return;
    }

    string method;
    if(selectedRequest.isFriendRequest == true)
    {
        method = kRequestAcceptFriendRequestKey;
        ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
        ApiComunicator::sharedInstance()->requestAcceptFriendRequest(defaults->userID, selectedRequest.senderID);
    }
    else
    {
        method = kRequestAcceptGroupInviteRequestKey;
        ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
        ApiComunicator::sharedInstance()->requestAcceptGroupInviteRequest(defaults->userID, selectedRequest.senderID);

    }

    selectedRequest.senderID = -1;
}

void GroupsAndPostsWidget::on_notificationsList_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
        selectedRequest = myRequestList[currentRow];

    }
}

void GroupsAndPostsWidget::on_pushButton_4_clicked()
{
    std::vector<int> listOfUserIds;
    QModelIndexList indexes = ui->myFriendList->selectionModel()->selectedIndexes();
    for(int i=0; i<indexes.size(); i++)
    {
        int userIndex = indexes[i].row();
        User aUser = myFriendsList[userIndex];
        listOfUserIds.push_back(aUser.userID);

        qDebug() << "did add "<<aUser.userID<<" to useridlist";
    }

    string method = kStartChatGroupRequest;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestStartChatGroupRequest(defaults->userID, listOfUserIds);
}

void GroupsAndPostsWidget::on_createGroupBtn_clicked()
{
    string name, description;

    name = ui->groupNameTF->text().toStdString();
    description = ui->groupDescriptionTF->text().toStdString();

    if(name.length() == 0 || description.length() == 0)
    {
        ui->groupCreateStatusLabel->setText("Please make sure no field is empty.");
        return;
    }

    string method = kRequestCreateGroupKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestCreateGroup(name, description, defaults->userID);
}

void GroupsAndPostsWidget::on_deletePostBtn_clicked()
{
    if(currentSelectedPost.postID == -1)
    {
        ui->deletePostStatusLabel->setText("Please select another post");
        return;
    }
    string method = kRequestDeletePostKey;
    ApiComunicator::sharedInstance()->setListenerForMethod(this, method);
    ApiComunicator::sharedInstance()->requestDeletePost(currentSelectedPost.postID, defaults->userID);

    currentSelectedPost.postID = -1;
}

void GroupsAndPostsWidget::on_logoutBtn_clicked()
{
    if(this->listener != NULL)
    {
        ApiComunicator::sharedInstance()->requestLogout(defaults->userID);
        listener->childWidgetWishesToClose(this);
    }
}

void GroupsAndPostsWidget::setListener(ChildWidgetListener *listener)
{
    this->listener = listener;
}
