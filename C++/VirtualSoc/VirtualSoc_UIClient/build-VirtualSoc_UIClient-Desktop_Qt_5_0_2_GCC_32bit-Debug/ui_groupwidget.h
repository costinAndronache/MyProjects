/********************************************************************************
** Form generated from reading UI file 'groupwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPWIDGET_H
#define UI_GROUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *groupDescLabel;
    QLabel *groupNameLabel;

    void setupUi(QWidget *GroupWidget)
    {
        if (GroupWidget->objectName().isEmpty())
            GroupWidget->setObjectName(QStringLiteral("GroupWidget"));
        GroupWidget->resize(283, 120);
        label = new QLabel(GroupWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 71, 16));
        label_2 = new QLabel(GroupWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 101, 16));
        groupDescLabel = new QLabel(GroupWidget);
        groupDescLabel->setObjectName(QStringLiteral("groupDescLabel"));
        groupDescLabel->setGeometry(QRect(110, 70, 111, 41));
        groupDescLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        groupNameLabel = new QLabel(GroupWidget);
        groupNameLabel->setObjectName(QStringLiteral("groupNameLabel"));
        groupNameLabel->setGeometry(QRect(110, 10, 111, 31));
        groupNameLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        retranslateUi(GroupWidget);

        QMetaObject::connectSlotsByName(GroupWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupWidget)
    {
        GroupWidget->setWindowTitle(QApplication::translate("GroupWidget", "Form", 0));
        label->setText(QApplication::translate("GroupWidget", "Group name:", 0));
        label_2->setText(QApplication::translate("GroupWidget", "Group description:", 0));
        groupDescLabel->setText(QApplication::translate("GroupWidget", "TextLabel", 0));
        groupNameLabel->setText(QApplication::translate("GroupWidget", "name here", 0));
    } // retranslateUi

};

namespace Ui {
    class GroupWidget: public Ui_GroupWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPWIDGET_H
