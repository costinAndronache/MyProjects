/********************************************************************************
** Form generated from reading UI file 'form_home.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_HOME_H
#define UI_FORM_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Home
{
public:
    QLabel *titleLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLineEdit *usernameTextField;
    QLabel *label_2;
    QLineEdit *passwordTextField;
    QSpacerItem *verticalSpacer;
    QPushButton *loginBtn;
    QPushButton *pushButton;
    QPushButton *registerBtn;

    void setupUi(QWidget *Form_Home)
    {
        if (Form_Home->objectName().isEmpty())
            Form_Home->setObjectName(QStringLiteral("Form_Home"));
        Form_Home->resize(402, 285);
        titleLabel = new QLabel(Form_Home);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setGeometry(QRect(140, 10, 131, 41));
        QFont font;
        font.setFamily(QStringLiteral("Loma"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget = new QWidget(Form_Home);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(130, 50, 160, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        usernameTextField = new QLineEdit(verticalLayoutWidget);
        usernameTextField->setObjectName(QStringLiteral("usernameTextField"));

        verticalLayout->addWidget(usernameTextField);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        passwordTextField = new QLineEdit(verticalLayoutWidget);
        passwordTextField->setObjectName(QStringLiteral("passwordTextField"));

        verticalLayout->addWidget(passwordTextField);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        loginBtn = new QPushButton(verticalLayoutWidget);
        loginBtn->setObjectName(QStringLiteral("loginBtn"));

        verticalLayout->addWidget(loginBtn);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        registerBtn = new QPushButton(verticalLayoutWidget);
        registerBtn->setObjectName(QStringLiteral("registerBtn"));

        verticalLayout->addWidget(registerBtn);


        retranslateUi(Form_Home);

        QMetaObject::connectSlotsByName(Form_Home);
    } // setupUi

    void retranslateUi(QWidget *Form_Home)
    {
        Form_Home->setWindowTitle(QApplication::translate("Form_Home", "Form", 0));
        titleLabel->setText(QApplication::translate("Form_Home", "VirtualSoc Login", 0));
        label_3->setText(QApplication::translate("Form_Home", "Username", 0));
        label_2->setText(QApplication::translate("Form_Home", "Password", 0));
        loginBtn->setText(QApplication::translate("Form_Home", "Login", 0));
        pushButton->setText(QApplication::translate("Form_Home", "Logout", 0));
        registerBtn->setText(QApplication::translate("Form_Home", "Register", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Home: public Ui_Form_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_HOME_H
