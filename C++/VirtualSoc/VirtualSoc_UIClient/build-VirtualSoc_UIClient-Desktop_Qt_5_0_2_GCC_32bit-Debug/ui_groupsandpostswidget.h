/********************************************************************************
** Form generated from reading UI file 'groupsandpostswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPSANDPOSTSWIDGET_H
#define UI_GROUPSANDPOSTSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "chatwidget.h"
#include "userinfowidget.h"

QT_BEGIN_NAMESPACE

class Ui_GroupsAndPostsWidget
{
public:
    QListWidget *groupListWidget;
    QListWidget *postListWidget;
    QPushButton *postListRefreshBtn;
    QLabel *label;
    QLabel *label_2;
    QPushButton *refreshGroupListBtn;
    QLabel *groupDescriptionLabel;
    QLabel *postContentLabel;
    QLabel *label_3;
    QLabel *label_4;
    UserInfoWidget *userInfoWidget;
    QPlainTextEdit *postContentTextEdit;
    QPushButton *sendPostBtn;
    QLabel *label_5;
    QListWidget *groupUsersList;
    QListWidget *myGroupsList;
    QListWidget *myFriendList;
    QPushButton *myGroupListBtn;
    QPushButton *listGroupUsersBtn;
    QPushButton *pushButton_3;
    QPushButton *sendFriendRequest;
    QPushButton *groupInviteBtn;
    QLabel *inviteStatusLabel;
    QLabel *label_6;
    QListWidget *notificationsList;
    QPushButton *pushButton;
    QLabel *label_7;
    QLabel *senderLabel;
    QPushButton *pushButton_2;
    QLabel *confirmLabel;
    ChatWidget *chatWidget;
    QPushButton *pushButton_4;
    QLabel *groupCreateStatusLabel;
    QLineEdit *groupNameTF;
    QLineEdit *groupDescriptionTF;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *createGroupBtn;
    QPushButton *deletePostBtn;
    QLabel *deletePostStatusLabel;
    QPushButton *logoutBtn;

    void setupUi(QWidget *GroupsAndPostsWidget)
    {
        if (GroupsAndPostsWidget->objectName().isEmpty())
            GroupsAndPostsWidget->setObjectName(QStringLiteral("GroupsAndPostsWidget"));
        GroupsAndPostsWidget->resize(1213, 800);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GroupsAndPostsWidget->sizePolicy().hasHeightForWidth());
        GroupsAndPostsWidget->setSizePolicy(sizePolicy);
        groupListWidget = new QListWidget(GroupsAndPostsWidget);
        groupListWidget->setObjectName(QStringLiteral("groupListWidget"));
        groupListWidget->setGeometry(QRect(10, 40, 151, 192));
        postListWidget = new QListWidget(GroupsAndPostsWidget);
        postListWidget->setObjectName(QStringLiteral("postListWidget"));
        postListWidget->setGeometry(QRect(440, 40, 141, 192));
        postListRefreshBtn = new QPushButton(GroupsAndPostsWidget);
        postListRefreshBtn->setObjectName(QStringLiteral("postListRefreshBtn"));
        postListRefreshBtn->setGeometry(QRect(450, 250, 111, 27));
        label = new QLabel(GroupsAndPostsWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 20, 141, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(GroupsAndPostsWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 20, 141, 20));
        label_2->setAlignment(Qt::AlignCenter);
        refreshGroupListBtn = new QPushButton(GroupsAndPostsWidget);
        refreshGroupListBtn->setObjectName(QStringLiteral("refreshGroupListBtn"));
        refreshGroupListBtn->setGeometry(QRect(20, 250, 111, 27));
        groupDescriptionLabel = new QLabel(GroupsAndPostsWidget);
        groupDescriptionLabel->setObjectName(QStringLiteral("groupDescriptionLabel"));
        groupDescriptionLabel->setGeometry(QRect(180, 80, 91, 141));
        groupDescriptionLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        groupDescriptionLabel->setWordWrap(true);
        postContentLabel = new QLabel(GroupsAndPostsWidget);
        postContentLabel->setObjectName(QStringLiteral("postContentLabel"));
        postContentLabel->setGeometry(QRect(330, 80, 91, 141));
        postContentLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        postContentLabel->setWordWrap(true);
        label_3 = new QLabel(GroupsAndPostsWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(188, 50, 61, 20));
        label_4 = new QLabel(GroupsAndPostsWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(340, 50, 61, 20));
        userInfoWidget = new UserInfoWidget(GroupsAndPostsWidget);
        userInfoWidget->setObjectName(QStringLiteral("userInfoWidget"));
        userInfoWidget->setGeometry(QRect(159, 239, 281, 81));
        postContentTextEdit = new QPlainTextEdit(GroupsAndPostsWidget);
        postContentTextEdit->setObjectName(QStringLiteral("postContentTextEdit"));
        postContentTextEdit->setGeometry(QRect(160, 330, 281, 91));
        sendPostBtn = new QPushButton(GroupsAndPostsWidget);
        sendPostBtn->setObjectName(QStringLiteral("sendPostBtn"));
        sendPostBtn->setGeometry(QRect(230, 430, 151, 27));
        label_5 = new QLabel(GroupsAndPostsWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(68, 350, 71, 71));
        label_5->setWordWrap(true);
        groupUsersList = new QListWidget(GroupsAndPostsWidget);
        groupUsersList->setObjectName(QStringLiteral("groupUsersList"));
        groupUsersList->setGeometry(QRect(10, 490, 131, 241));
        myGroupsList = new QListWidget(GroupsAndPostsWidget);
        myGroupsList->setObjectName(QStringLiteral("myGroupsList"));
        myGroupsList->setGeometry(QRect(280, 490, 141, 241));
        myFriendList = new QListWidget(GroupsAndPostsWidget);
        myFriendList->setObjectName(QStringLiteral("myFriendList"));
        myFriendList->setGeometry(QRect(470, 491, 141, 241));
        myFriendList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        myGroupListBtn = new QPushButton(GroupsAndPostsWidget);
        myGroupListBtn->setObjectName(QStringLiteral("myGroupListBtn"));
        myGroupListBtn->setGeometry(QRect(290, 750, 121, 27));
        listGroupUsersBtn = new QPushButton(GroupsAndPostsWidget);
        listGroupUsersBtn->setObjectName(QStringLiteral("listGroupUsersBtn"));
        listGroupUsersBtn->setGeometry(QRect(14, 750, 121, 27));
        pushButton_3 = new QPushButton(GroupsAndPostsWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(480, 750, 121, 27));
        sendFriendRequest = new QPushButton(GroupsAndPostsWidget);
        sendFriendRequest->setObjectName(QStringLiteral("sendFriendRequest"));
        sendFriendRequest->setGeometry(QRect(144, 530, 121, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sendFriendRequest->sizePolicy().hasHeightForWidth());
        sendFriendRequest->setSizePolicy(sizePolicy1);
        sendFriendRequest->setAutoDefault(false);
        sendFriendRequest->setFlat(false);
        groupInviteBtn = new QPushButton(GroupsAndPostsWidget);
        groupInviteBtn->setObjectName(QStringLiteral("groupInviteBtn"));
        groupInviteBtn->setGeometry(QRect(144, 606, 121, 41));
        inviteStatusLabel = new QLabel(GroupsAndPostsWidget);
        inviteStatusLabel->setObjectName(QStringLiteral("inviteStatusLabel"));
        inviteStatusLabel->setGeometry(QRect(158, 690, 91, 51));
        label_6 = new QLabel(GroupsAndPostsWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(770, 20, 49, 14));
        notificationsList = new QListWidget(GroupsAndPostsWidget);
        notificationsList->setObjectName(QStringLiteral("notificationsList"));
        notificationsList->setGeometry(QRect(730, 41, 151, 191));
        pushButton = new QPushButton(GroupsAndPostsWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(730, 250, 151, 27));
        label_7 = new QLabel(GroupsAndPostsWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(900, 80, 81, 20));
        senderLabel = new QLabel(GroupsAndPostsWidget);
        senderLabel->setObjectName(QStringLiteral("senderLabel"));
        senderLabel->setGeometry(QRect(900, 100, 81, 31));
        pushButton_2 = new QPushButton(GroupsAndPostsWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(900, 150, 85, 27));
        confirmLabel = new QLabel(GroupsAndPostsWidget);
        confirmLabel->setObjectName(QStringLiteral("confirmLabel"));
        confirmLabel->setGeometry(QRect(898, 200, 81, 31));
        chatWidget = new ChatWidget(GroupsAndPostsWidget);
        chatWidget->setObjectName(QStringLiteral("chatWidget"));
        chatWidget->setGeometry(QRect(800, 400, 401, 391));
        pushButton_4 = new QPushButton(GroupsAndPostsWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(620, 700, 111, 27));
        groupCreateStatusLabel = new QLabel(GroupsAndPostsWidget);
        groupCreateStatusLabel->setObjectName(QStringLiteral("groupCreateStatusLabel"));
        groupCreateStatusLabel->setGeometry(QRect(530, 310, 241, 20));
        groupNameTF = new QLineEdit(GroupsAndPostsWidget);
        groupNameTF->setObjectName(QStringLiteral("groupNameTF"));
        groupNameTF->setGeometry(QRect(590, 330, 171, 24));
        groupDescriptionTF = new QLineEdit(GroupsAndPostsWidget);
        groupDescriptionTF->setObjectName(QStringLiteral("groupDescriptionTF"));
        groupDescriptionTF->setGeometry(QRect(590, 360, 171, 24));
        label_9 = new QLabel(GroupsAndPostsWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(550, 330, 31, 20));
        label_10 = new QLabel(GroupsAndPostsWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(520, 360, 61, 20));
        createGroupBtn = new QPushButton(GroupsAndPostsWidget);
        createGroupBtn->setObjectName(QStringLiteral("createGroupBtn"));
        createGroupBtn->setGeometry(QRect(590, 390, 85, 27));
        deletePostBtn = new QPushButton(GroupsAndPostsWidget);
        deletePostBtn->setObjectName(QStringLiteral("deletePostBtn"));
        deletePostBtn->setGeometry(QRect(600, 170, 111, 27));
        deletePostStatusLabel = new QLabel(GroupsAndPostsWidget);
        deletePostStatusLabel->setObjectName(QStringLiteral("deletePostStatusLabel"));
        deletePostStatusLabel->setGeometry(QRect(600, 70, 101, 61));
        deletePostStatusLabel->setAlignment(Qt::AlignCenter);
        deletePostStatusLabel->setWordWrap(true);
        logoutBtn = new QPushButton(GroupsAndPostsWidget);
        logoutBtn->setObjectName(QStringLiteral("logoutBtn"));
        logoutBtn->setGeometry(QRect(1070, 70, 85, 27));

        retranslateUi(GroupsAndPostsWidget);

        QMetaObject::connectSlotsByName(GroupsAndPostsWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupsAndPostsWidget)
    {
        GroupsAndPostsWidget->setWindowTitle(QApplication::translate("GroupsAndPostsWidget", "Form", 0));
        postListRefreshBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Refesh post list", 0));
        label->setText(QApplication::translate("GroupsAndPostsWidget", "Groups", 0));
        label_2->setText(QApplication::translate("GroupsAndPostsWidget", "Posts", 0));
        refreshGroupListBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Refresh group List", 0));
        groupDescriptionLabel->setText(QString());
        postContentLabel->setText(QString());
        label_3->setText(QApplication::translate("GroupsAndPostsWidget", "Description", 0));
        label_4->setText(QApplication::translate("GroupsAndPostsWidget", "Contents", 0));
        sendPostBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Send post to selected group", 0));
        label_5->setText(QString());
        myGroupListBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Refresh my group list", 0));
        listGroupUsersBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Refresh group users", 0));
        pushButton_3->setText(QApplication::translate("GroupsAndPostsWidget", "Refresh my friend list", 0));
        sendFriendRequest->setText(QApplication::translate("GroupsAndPostsWidget", "Send friend request ", 0));
        groupInviteBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Invite into my group", 0));
        inviteStatusLabel->setText(QString());
        label_6->setText(QApplication::translate("GroupsAndPostsWidget", "Requests", 0));
        pushButton->setText(QApplication::translate("GroupsAndPostsWidget", "Refresh notification list", 0));
        label_7->setText(QApplication::translate("GroupsAndPostsWidget", "Sender/Group:", 0));
        senderLabel->setText(QString());
        pushButton_2->setText(QApplication::translate("GroupsAndPostsWidget", "Confirm", 0));
        confirmLabel->setText(QString());
        pushButton_4->setText(QApplication::translate("GroupsAndPostsWidget", "Start a chat group", 0));
        groupCreateStatusLabel->setText(QApplication::translate("GroupsAndPostsWidget", "Create a new group", 0));
        label_9->setText(QApplication::translate("GroupsAndPostsWidget", "Name", 0));
        label_10->setText(QApplication::translate("GroupsAndPostsWidget", "Description", 0));
        createGroupBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Create group", 0));
        deletePostBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Delete selected post", 0));
        deletePostStatusLabel->setText(QString());
        logoutBtn->setText(QApplication::translate("GroupsAndPostsWidget", "Logout", 0));
    } // retranslateUi

};

namespace Ui {
    class GroupsAndPostsWidget: public Ui_GroupsAndPostsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPSANDPOSTSWIDGET_H
