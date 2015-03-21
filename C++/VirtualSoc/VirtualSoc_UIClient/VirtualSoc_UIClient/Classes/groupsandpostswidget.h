#ifndef GROUPSANDPOSTSWIDGET_H
#define GROUPSANDPOSTSWIDGET_H

#include <QWidget>
#include "ApiComunicator.h"
#include "groupwidget.h"
#include "postwidget.h"
#include "userdefaults.h"
#include <QVector>
#include "userinfowidget.h"
#include "ChildWidgetListener.h"

namespace Ui {
class GroupsAndPostsWidget;
}

class GroupsAndPostsWidget : public QWidget, public ApiComunicatorListener
{
    Q_OBJECT
    
public:
    explicit GroupsAndPostsWidget(QWidget *parent = 0);
    ~GroupsAndPostsWidget();

    void didReceiveJSONFromComunicator(string &message);
    void setListener(ChildWidgetListener *listener);
private slots:

    void on_refreshGroupListBtn_clicked();

    void on_groupListWidget_currentRowChanged(int currentRow);

    void on_postListRefreshBtn_clicked();

    void on_postListWidget_currentRowChanged(int currentRow);

    void on_sendPostBtn_clicked();

    void on_listGroupUsersBtn_clicked();

    void on_pushButton_3_clicked();

    void on_groupUsersList_currentRowChanged(int currentRow);

    void on_myFriendList_currentRowChanged(int currentRow);

    void on_myGroupListBtn_clicked();

    void on_myGroupsList_currentRowChanged(int currentRow);

    void on_sendFriendRequest_clicked();

    void on_groupInviteBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_notificationsList_currentRowChanged(int currentRow);

    void on_pushButton_4_clicked();

    void on_createGroupBtn_clicked();

    void on_deletePostBtn_clicked();

    void on_logoutBtn_clicked();

private:
    Ui::GroupsAndPostsWidget *ui;

    void setupGroupListWithJson(Json::Value &val);
    void setupPostListWithJson(Json::Value &val);
    void setupMyGroupsListWithJson(Json::Value &val);
    void setupMyFriendsListWithJson(Json::Value &val);
    void setupListOfGroupUsersWithJson(Json::Value &val);
    void setupNotificationsListWithJson(Json::Value &val);

    QVector<Group> groupList;
    QVector<Group> myGroupList;
    QVector<Post> postList;

    QVector<Request> myRequestList;
    QVector<User> myFriendsList;
    QVector<User> usersFromGroupList;

    Group currentSelectedGroup, myLastSelectedGroup;
    Post currentSelectedPost;
    User currentSelectedUser, myLastSelectedFriend;
    Request selectedRequest;

    UserDefaults *defaults;
    ChildWidgetListener *listener;
};

#endif // GROUPSANDPOSTSWIDGET_H
