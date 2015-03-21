/********************************************************************************
** Form generated from reading UI file 'userinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFOWIDGET_H
#define UI_USERINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInfoWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *firstNameLabel;
    QLabel *infoLabel;
    QLabel *lastNameLabel;

    void setupUi(QWidget *UserInfoWidget)
    {
        if (UserInfoWidget->objectName().isEmpty())
            UserInfoWidget->setObjectName(QStringLiteral("UserInfoWidget"));
        UserInfoWidget->resize(243, 84);
        label = new QLabel(UserInfoWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 51, 16));
        label_2 = new QLabel(UserInfoWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 51, 20));
        label_3 = new QLabel(UserInfoWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 60, 49, 14));
        firstNameLabel = new QLabel(UserInfoWidget);
        firstNameLabel->setObjectName(QStringLiteral("firstNameLabel"));
        firstNameLabel->setGeometry(QRect(90, 10, 161, 16));
        infoLabel = new QLabel(UserInfoWidget);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(70, 60, 161, 16));
        lastNameLabel = new QLabel(UserInfoWidget);
        lastNameLabel->setObjectName(QStringLiteral("lastNameLabel"));
        lastNameLabel->setGeometry(QRect(90, 30, 151, 20));

        retranslateUi(UserInfoWidget);

        QMetaObject::connectSlotsByName(UserInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *UserInfoWidget)
    {
        UserInfoWidget->setWindowTitle(QApplication::translate("UserInfoWidget", "Form", 0));
        label->setText(QApplication::translate("UserInfoWidget", "First name", 0));
        label_2->setText(QApplication::translate("UserInfoWidget", "Last name", 0));
        label_3->setText(QApplication::translate("UserInfoWidget", "Info", 0));
        firstNameLabel->setText(QString());
        infoLabel->setText(QString());
        lastNameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserInfoWidget: public Ui_UserInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFOWIDGET_H
