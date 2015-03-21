/********************************************************************************
** Form generated from reading UI file 'hometabwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMETABWIDGET_H
#define UI_HOMETABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeTabWidget
{
public:

    void setupUi(QWidget *HomeTabWidget)
    {
        if (HomeTabWidget->objectName().isEmpty())
            HomeTabWidget->setObjectName(QStringLiteral("HomeTabWidget"));
        HomeTabWidget->resize(400, 300);

        retranslateUi(HomeTabWidget);

        QMetaObject::connectSlotsByName(HomeTabWidget);
    } // setupUi

    void retranslateUi(QWidget *HomeTabWidget)
    {
        HomeTabWidget->setWindowTitle(QApplication::translate("HomeTabWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeTabWidget: public Ui_HomeTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMETABWIDGET_H
