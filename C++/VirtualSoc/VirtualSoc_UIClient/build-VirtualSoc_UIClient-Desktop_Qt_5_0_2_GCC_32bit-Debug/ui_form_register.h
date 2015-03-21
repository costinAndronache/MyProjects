/********************************************************************************
** Form generated from reading UI file 'form_register.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_REGISTER_H
#define UI_FORM_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Register
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *usernameTF;
    QLineEdit *passwordTF;
    QLineEdit *firstNameTF;
    QLineEdit *lastNameTF;
    QLineEdit *someInfoTF;
    QPushButton *registerBtn;
    QLabel *resultLabel;
    QPushButton *loginBtn;
    QLabel *label_7;
    QLineEdit *adminCodeTF;

    void setupUi(QWidget *Form_Register)
    {
        if (Form_Register->objectName().isEmpty())
            Form_Register->setObjectName(QStringLiteral("Form_Register"));
        Form_Register->resize(372, 326);
        label = new QLabel(Form_Register);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 20, 111, 41));
        QFont font;
        font.setFamily(QStringLiteral("Loma"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Form_Register);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 90, 111, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Loma"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setTextFormat(Qt::PlainText);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Form_Register);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 120, 91, 41));
        label_3->setFont(font1);
        label_3->setTextFormat(Qt::PlainText);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(Form_Register);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 150, 111, 41));
        label_4->setFont(font1);
        label_4->setTextFormat(Qt::PlainText);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(Form_Register);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 180, 111, 41));
        label_5->setFont(font1);
        label_5->setTextFormat(Qt::PlainText);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(Form_Register);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 210, 111, 41));
        label_6->setFont(font1);
        label_6->setTextFormat(Qt::PlainText);
        label_6->setAlignment(Qt::AlignCenter);
        usernameTF = new QLineEdit(Form_Register);
        usernameTF->setObjectName(QStringLiteral("usernameTF"));
        usernameTF->setGeometry(QRect(150, 100, 151, 24));
        passwordTF = new QLineEdit(Form_Register);
        passwordTF->setObjectName(QStringLiteral("passwordTF"));
        passwordTF->setGeometry(QRect(150, 130, 151, 24));
        firstNameTF = new QLineEdit(Form_Register);
        firstNameTF->setObjectName(QStringLiteral("firstNameTF"));
        firstNameTF->setGeometry(QRect(150, 160, 151, 24));
        lastNameTF = new QLineEdit(Form_Register);
        lastNameTF->setObjectName(QStringLiteral("lastNameTF"));
        lastNameTF->setGeometry(QRect(150, 190, 151, 24));
        someInfoTF = new QLineEdit(Form_Register);
        someInfoTF->setObjectName(QStringLiteral("someInfoTF"));
        someInfoTF->setGeometry(QRect(150, 220, 151, 24));
        registerBtn = new QPushButton(Form_Register);
        registerBtn->setObjectName(QStringLiteral("registerBtn"));
        registerBtn->setGeometry(QRect(190, 290, 85, 27));
        resultLabel = new QLabel(Form_Register);
        resultLabel->setObjectName(QStringLiteral("resultLabel"));
        resultLabel->setGeometry(QRect(80, 60, 251, 16));
        QFont font2;
        font2.setFamily(QStringLiteral("Loma"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        resultLabel->setFont(font2);
        resultLabel->setAlignment(Qt::AlignCenter);
        loginBtn = new QPushButton(Form_Register);
        loginBtn->setObjectName(QStringLiteral("loginBtn"));
        loginBtn->setGeometry(QRect(50, 290, 85, 27));
        label_7 = new QLabel(Form_Register);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 240, 111, 41));
        label_7->setFont(font1);
        label_7->setTextFormat(Qt::PlainText);
        label_7->setAlignment(Qt::AlignCenter);
        adminCodeTF = new QLineEdit(Form_Register);
        adminCodeTF->setObjectName(QStringLiteral("adminCodeTF"));
        adminCodeTF->setGeometry(QRect(190, 250, 113, 24));

        retranslateUi(Form_Register);

        QMetaObject::connectSlotsByName(Form_Register);
    } // setupUi

    void retranslateUi(QWidget *Form_Register)
    {
        Form_Register->setWindowTitle(QApplication::translate("Form_Register", "Form", 0));
        label->setText(QApplication::translate("Form_Register", "Register", 0));
        label_2->setText(QApplication::translate("Form_Register", "Username", 0));
        label_3->setText(QApplication::translate("Form_Register", "Password", 0));
        label_4->setText(QApplication::translate("Form_Register", "First name", 0));
        label_5->setText(QApplication::translate("Form_Register", "Last name", 0));
        label_6->setText(QApplication::translate("Form_Register", "Some info", 0));
        registerBtn->setText(QApplication::translate("Form_Register", "Register", 0));
        resultLabel->setText(QString());
        loginBtn->setText(QApplication::translate("Form_Register", "Login", 0));
        label_7->setText(QApplication::translate("Form_Register", "Admin code?", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_Register: public Ui_Form_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_REGISTER_H
