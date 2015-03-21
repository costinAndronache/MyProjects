/********************************************************************************
** Form generated from reading UI file 'postwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTWIDGET_H
#define UI_POSTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PostWidget
{
public:
    QLabel *contentsLabel;
    QLabel *firstNameLabel;
    QLabel *lastNameLabel;

    void setupUi(QWidget *PostWidget)
    {
        if (PostWidget->objectName().isEmpty())
            PostWidget->setObjectName(QStringLiteral("PostWidget"));
        PostWidget->resize(328, 92);
        contentsLabel = new QLabel(PostWidget);
        contentsLabel->setObjectName(QStringLiteral("contentsLabel"));
        contentsLabel->setGeometry(QRect(10, 10, 301, 41));
        contentsLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        firstNameLabel = new QLabel(PostWidget);
        firstNameLabel->setObjectName(QStringLiteral("firstNameLabel"));
        firstNameLabel->setGeometry(QRect(10, 60, 61, 16));
        lastNameLabel = new QLabel(PostWidget);
        lastNameLabel->setObjectName(QStringLiteral("lastNameLabel"));
        lastNameLabel->setGeometry(QRect(140, 60, 121, 21));

        retranslateUi(PostWidget);

        QMetaObject::connectSlotsByName(PostWidget);
    } // setupUi

    void retranslateUi(QWidget *PostWidget)
    {
        PostWidget->setWindowTitle(QApplication::translate("PostWidget", "Form", 0));
        contentsLabel->setText(QApplication::translate("PostWidget", "TextLabel", 0));
        firstNameLabel->setText(QApplication::translate("PostWidget", "TextLabel", 0));
        lastNameLabel->setText(QApplication::translate("PostWidget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class PostWidget: public Ui_PostWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTWIDGET_H
