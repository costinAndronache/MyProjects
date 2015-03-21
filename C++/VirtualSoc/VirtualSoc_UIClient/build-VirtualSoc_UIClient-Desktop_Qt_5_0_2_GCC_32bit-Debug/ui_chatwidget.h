/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendBtn;
    QPushButton *disconnectBtn;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QStringLiteral("ChatWidget"));
        ChatWidget->resize(313, 330);
        textEdit = new QTextEdit(ChatWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 281, 251));
        lineEdit = new QLineEdit(ChatWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 270, 221, 24));
        sendBtn = new QPushButton(ChatWidget);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setGeometry(QRect(240, 270, 61, 27));
        disconnectBtn = new QPushButton(ChatWidget);
        disconnectBtn->setObjectName(QStringLiteral("disconnectBtn"));
        disconnectBtn->setGeometry(QRect(100, 296, 85, 31));

        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QApplication::translate("ChatWidget", "Form", 0));
        sendBtn->setText(QApplication::translate("ChatWidget", "Send", 0));
        disconnectBtn->setText(QApplication::translate("ChatWidget", "Disconnect", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
