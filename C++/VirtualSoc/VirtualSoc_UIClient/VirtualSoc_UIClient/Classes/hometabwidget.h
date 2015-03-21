#ifndef HOMETABWIDGET_H
#define HOMETABWIDGET_H

#include <QWidget>
#include "ChildWidgetListener.h"
#include "form_home.h"
#include "form_register.h"
#include "groupsandpostswidget.h"

namespace Ui {
class HomeTabWidget;
}

class HomeTabWidget : public QWidget, public ChildWidgetListener
{
    Q_OBJECT
    
public:
    explicit HomeTabWidget(QWidget *parent = 0);
    void childWidgetWishesToClose(QWidget *theChild);
    void loginWidgetFinishedLoggingIn(QWidget *theChild);
    ~HomeTabWidget();
    
private:
    Ui::HomeTabWidget *ui;
    Form_Home *loginForm;
    Form_Register *registerForm;
    GroupsAndPostsWidget *mainWidget;
};

#endif // HOMETABWIDGET_H
